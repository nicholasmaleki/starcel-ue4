// Copyright Epic Games, Inc. All Rights Reserved.

#include "Text3DComponent.h"
#include "Text3DPrivate.h"
#include "TextShaper.h"
#include "MeshCreator.h"
#include "Glyph.h"

#include "ContourList.h"
#include "Data.h"
#include "Text3DEngineSubsystem.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/Font.h"
#include "Engine/Engine.h"
#include "Materials/Material.h"
#include "UObject/ConstructorHelpers.h"


#define LOCTEXT_NAMESPACE "Text3D"

struct FText3DShapedText
{
	FText3DShapedText()
	{
		Reset();
	}

	void Reset()
	{
		LineHeight = 0.0f;
		FontAscender = 0.0f;
		FontDescender = 0.0f;
		Lines.Reset();
	}

	float LineHeight;
	float FontAscender;
	float FontDescender;
	TArray<struct FShapedGlyphLine> Lines;
};

using TTextMeshDynamicData = TArray<TUniquePtr<FText3DDynamicData>, TFixedAllocator<static_cast<int32>(EText3DGroupType::TypeCount)>>;


UText3DComponent::UText3DComponent() :
	ShapedText(new FText3DShapedText())
{
	TextRoot = CreateDefaultSubobject<USceneComponent>(TEXT("TextRoot"));
#if WITH_EDITOR
	TextRoot->SetIsVisualizationComponent(true);
#endif

	if (!IsRunningDedicatedServer())
	{
		struct FConstructorStatics
		{
			ConstructorHelpers::FObjectFinder<UFont> Font;
			ConstructorHelpers::FObjectFinder<UMaterial> Material;
			FConstructorStatics()
				: Font(TEXT("/Engine/EngineFonts/Roboto"))
				, Material(TEXT("/Engine/BasicShapes/BasicShapeMaterial"))
			{
			}
		};
		static FConstructorStatics ConstructorStatics;

		Font = ConstructorStatics.Font.Object;
		UMaterial* DefaultMaterial = ConstructorStatics.Material.Object;
		FrontMaterial = DefaultMaterial;
		BevelMaterial = DefaultMaterial;
		ExtrudeMaterial = DefaultMaterial;
		BackMaterial = DefaultMaterial;
	}

	Text = LOCTEXT("DefaultText", "Text");
	bOutline = false;
	Extrude = 5.0f;
	Bevel = 0.0f;
	BevelType = EText3DBevelType::Convex;
	BevelSegments = 8;

	HorizontalAlignment = EText3DHorizontalTextAlignment::Left;
	VerticalAlignment = EText3DVerticalTextAlignment::FirstLine;
	Kerning = 0.0f;
	LineSpacing = 0.0f;
	WordSpacing = 0.0f;

	bHasMaxWidth = false;
	MaxWidth = 500.f;
	bHasMaxHeight = false;
	MaxHeight = 500.0f;
	bScaleProportionally = true;

	bPendingBuild = false;
	bFreezeBuild = false;
}

void UText3DComponent::OnRegister()
{
	Super::OnRegister();
	TextRoot->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	BuildTextMesh();
}

void UText3DComponent::OnUnregister()
{
	ClearTextMesh();
	Super::OnUnregister();
}

#if WITH_EDITOR
void UText3DComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	static FName BevelTypePropertyName = GET_MEMBER_NAME_CHECKED(UText3DComponent, BevelType);
	static FName BevelSegmentsPropertyName = GET_MEMBER_NAME_CHECKED(UText3DComponent, BevelSegments);

	const FName Name = PropertyChangedEvent.GetPropertyName();
	if (Name == BevelTypePropertyName)
	{
		switch (BevelType)
		{
		case EText3DBevelType::Linear:
		case EText3DBevelType::OneStep:
		case EText3DBevelType::TwoSteps:
		case EText3DBevelType::Engraved:
		{
			BevelSegments = 1;
			break;
		}
		case EText3DBevelType::Convex:
		case EText3DBevelType::Concave:
		{
			BevelSegments = 8;
			break;
		}
		case EText3DBevelType::HalfCircle:
		{
			BevelSegments = 16;
			break;
		}
		}
	}
	else if (Name == BevelSegmentsPropertyName)
	{
		// Force minimum bevel segments based on the BevelType
		SetBevelSegments(BevelSegments);
	}
}
#endif

void UText3DComponent::SetText(const FText& Value)
{
	if (!Text.EqualTo(Value))
	{
		Text = Value;
		Rebuild();
	}
}

void UText3DComponent::SetFont(UFont* const InFont)
{
	if (Font != InFont)
	{
		Font = InFont;
		Rebuild();
	}
}

void UText3DComponent::SetOutline(const bool bValue)
{
	if (bOutline != bValue)
	{
		bOutline = bValue;
		Rebuild();
	}
}

void UText3DComponent::SetExtrude(const float Value)
{
	const float NewValue = FMath::Max(0.0f, Value);
	if (!FMath::IsNearlyEqual(Extrude, NewValue))
	{
		Extrude = NewValue;
		CheckBevel();
		Rebuild();
	}
}

void UText3DComponent::SetBevel(const float Value)
{
	const float NewValue = FMath::Clamp(Value, 0.f, MaxBevel());

	if (!FMath::IsNearlyEqual(Bevel, NewValue))
	{
		Bevel = NewValue;
		Rebuild();
	}
}

void UText3DComponent::SetBevelType(const EText3DBevelType Value)
{
	if (BevelType != Value)
	{
		BevelType = Value;
		Rebuild();
	}
}

void UText3DComponent::SetBevelSegments(const int32 Value)
{
	int32 MinBevelSegments = 1;
	if (BevelType == EText3DBevelType::HalfCircle)
	{
		MinBevelSegments = 2;
	}

	const int32 NewValue = FMath::Clamp(Value, MinBevelSegments, 15);
	if (BevelSegments != NewValue)
	{
		BevelSegments = NewValue;
		Rebuild();
	}
}

void UText3DComponent::SetFrontMaterial(UMaterialInterface* Value)
{
	SetMaterial(EText3DGroupType::Front, Value);
}

void UText3DComponent::SetBevelMaterial(UMaterialInterface* Value)
{
	SetMaterial(EText3DGroupType::Bevel, Value);
}

void UText3DComponent::SetExtrudeMaterial(UMaterialInterface* Value)
{
	SetMaterial(EText3DGroupType::Extrude, Value);
}

void UText3DComponent::SetBackMaterial(UMaterialInterface* Value)
{
	SetMaterial(EText3DGroupType::Back, Value);
}

UMaterialInterface* UText3DComponent::GetMaterial(const EText3DGroupType Type) const
{
	switch (Type)
	{
	case EText3DGroupType::Front:
	{
		return FrontMaterial;
	}

	case EText3DGroupType::Bevel:
	{
		return BevelMaterial;
	}

	case EText3DGroupType::Extrude:
	{
		return ExtrudeMaterial;
	}

	case EText3DGroupType::Back:
	{
		return BackMaterial;
	}
	}

	return nullptr;
}

void UText3DComponent::SetMaterial(const EText3DGroupType Type, UMaterialInterface* Value)
{
	UMaterialInterface* OldMaterial = GetMaterial(Type);
	if (Value != OldMaterial)
	{
		switch(Type)
		{
		case EText3DGroupType::Front:
		{
			FrontMaterial = Value;
			break;
		}

		case EText3DGroupType::Back:
		{
			BackMaterial = Value;
			break;
		}

		case EText3DGroupType::Extrude:
		{
			ExtrudeMaterial = Value;
			break;
		}

		case EText3DGroupType::Bevel:
		{
			BevelMaterial = Value;
			break;
		}
		}

		UpdateMaterial(Type, Value);
	}
}

void UText3DComponent::SetKerning(const float Value)
{
	if (!FMath::IsNearlyEqual(Kerning, Value))
	{
		Kerning = Value;
		UpdateTransforms();
	}
}

void UText3DComponent::SetLineSpacing(const float Value)
{
	if (!FMath::IsNearlyEqual(LineSpacing, Value))
	{
		LineSpacing = Value;
		UpdateTransforms();
	}
}

void UText3DComponent::SetWordSpacing(const float Value)
{
	if (!FMath::IsNearlyEqual(WordSpacing, Value))
	{
		WordSpacing = Value;
		UpdateTransforms();
	}
}

void UText3DComponent::SetHorizontalAlignment(const EText3DHorizontalTextAlignment Value)
{
	if (HorizontalAlignment != Value)
	{
		HorizontalAlignment = Value;
		UpdateTransforms();
	}
}

void UText3DComponent::SetVerticalAlignment(const EText3DVerticalTextAlignment Value)
{
	if (VerticalAlignment != Value)
	{
		VerticalAlignment = Value;
		UpdateTransforms();
	}
}

void UText3DComponent::SetHasMaxWidth(const bool Value)
{
	if (bHasMaxWidth != Value)
	{
		bHasMaxWidth = Value;
		UpdateTransforms();
	}
}

void UText3DComponent::SetMaxWidth(const float Value)
{
	const float NewValue = FMath::Max(1.0f, Value);
	if (!FMath::IsNearlyEqual(MaxWidth, NewValue))
	{
		MaxWidth = NewValue;
		UpdateTransforms();
	}
}

void UText3DComponent::SetHasMaxHeight(const bool Value)
{
	if (bHasMaxHeight != Value)
	{
		bHasMaxHeight = Value;
		UpdateTransforms();
	}
}

void UText3DComponent::SetMaxHeight(const float Value)
{
	const float NewValue = FMath::Max(1.0f, Value);
	if (!FMath::IsNearlyEqual(MaxHeight, NewValue))
	{
		MaxHeight = NewValue;
		UpdateTransforms();
	}
}

void UText3DComponent::SetScaleProportionally(const bool Value)
{
	if (bScaleProportionally != Value)
	{
		bScaleProportionally = Value;
		UpdateTransforms();
	}
}

void UText3DComponent::SetFreeze(const bool bFreeze)
{
	bFreezeBuild = bFreeze;
	if (bFreeze)
	{
		bPendingBuild = false;
	}
	else if (bPendingBuild)
	{
		Rebuild();
	}
}

int32 UText3DComponent::GetGlyphCount()
{
	return TextRoot->GetNumChildrenComponents();
}

USceneComponent* UText3DComponent::GetGlyphKerningComponent(int32 Index)
{
	if (Index < 0 || Index >= CharacterKernings.Num())
	{
		return nullptr;
	}

	return CharacterKernings[Index];
}

UStaticMeshComponent* UText3DComponent::GetGlyphMeshComponent(int32 Index)
{
	if (Index < 0 || Index >= CharacterMeshes.Num())
	{
		return nullptr;
	}

	return CharacterMeshes[Index];
}

void UText3DComponent::Rebuild()
{
	bPendingBuild = true;
	if (!bFreezeBuild)
	{
		BuildTextMesh();
	}
}
void UText3DComponent::CalculateTextWidth()
{
	for (FShapedGlyphLine& ShapedLine : ShapedText->Lines)
	{
		ShapedLine.CalculateWidth(Kerning, WordSpacing);
	}
}

float UText3DComponent::GetTextHeight()
{
	return ShapedText->Lines.Num() * ShapedText->LineHeight + (ShapedText->Lines.Num() - 1) * LineSpacing;
}

FVector UText3DComponent::GetTextScale()
{
	FVector Scale(1.0f, 1.0f, 1.0f);

	float TextMaxWidth = 0.0f;
	for (const FShapedGlyphLine& ShapedLine : ShapedText->Lines)
	{
		TextMaxWidth = FMath::Max(TextMaxWidth, ShapedLine.Width);
	}

	if (bHasMaxWidth && TextMaxWidth > MaxWidth && TextMaxWidth > 0.0f)
	{
		Scale.Y *= MaxWidth / TextMaxWidth;
		if (bScaleProportionally)
		{
			Scale.Z = Scale.Y;
		}
	}

	const float TotalHeight = GetTextHeight();
	if (bHasMaxHeight && TotalHeight > MaxHeight && TotalHeight > 0.0f)
	{
		Scale.Z *= MaxHeight / TotalHeight;
		if (bScaleProportionally)
		{
			Scale.Y = Scale.Z;
		}
	}

	if (bScaleProportionally)
	{
		Scale.X = Scale.Y;
	}

	return Scale;
}

FVector UText3DComponent::GetLineLocation(int32 LineIndex)
{
	float HorizontalOffset = 0.0f, VerticalOffset = 0.0f;
	if (LineIndex < 0 || LineIndex >= ShapedText->Lines.Num())
	{
		return FVector();
	}

	const FShapedGlyphLine& ShapedLine = ShapedText->Lines[LineIndex];

	if (HorizontalAlignment == EText3DHorizontalTextAlignment::Center)
	{
		HorizontalOffset = -ShapedLine.Width * 0.5f;
	}
	else if (HorizontalAlignment == EText3DHorizontalTextAlignment::Right)
	{
		HorizontalOffset = -ShapedLine.Width;
	}

	const float TotalHeight = GetTextHeight();
	if (VerticalAlignment != EText3DVerticalTextAlignment::FirstLine)
	{
		// First align it to Top
		VerticalOffset -= ShapedText->FontAscender;

		if (VerticalAlignment == EText3DVerticalTextAlignment::Center)
		{
			VerticalOffset += TotalHeight * 0.5f;
		}
		else if (VerticalAlignment == EText3DVerticalTextAlignment::Bottom)
		{
			VerticalOffset += TotalHeight + ShapedText->FontDescender;
		}
	}

	VerticalOffset -= LineIndex * (ShapedText->LineHeight + LineSpacing);

	return FVector(0.0f, HorizontalOffset, VerticalOffset);
}

void UText3DComponent::UpdateTransforms()
{
	CalculateTextWidth();
	FVector Scale = GetTextScale();
	TextRoot->SetRelativeScale3D(Scale);

	int32 GlyphIndex = 0;
	for (int32 LineIndex = 0; LineIndex < ShapedText->Lines.Num(); LineIndex++)
	{
		FShapedGlyphLine& Line = ShapedText->Lines[LineIndex];
		FVector Location = GetLineLocation(LineIndex);

		for (int32 LineGlyph = 0; LineGlyph < Line.GlyphsToRender.Num(); LineGlyph++)
		{
			FVector CharLocation = Location;
			Location.Y += Line.GetAdvanced(LineGlyph, Kerning, WordSpacing);
			if (!Line.GlyphsToRender[LineGlyph].bIsVisible)
			{
				continue;
			}

			USceneComponent* GlyphKerningComponent = GetGlyphKerningComponent(GlyphIndex);
			if (GlyphKerningComponent)
			{
				GlyphKerningComponent->SetRelativeLocation(CharLocation);
			}

			GlyphIndex++;
		}

		Location.Z -= ShapedText->LineHeight + LineSpacing;
	}
}

void UText3DComponent::ClearTextMesh()
{
	TArray<UActorComponent*> Boxes;
	GetOwner()->GetComponents(UBoxComponent::StaticClass(), Boxes);

	for (UActorComponent* Comp : Boxes)
	{
		if (Comp && Comp->GetName().Contains(TEXT("Text3D_Bounds")))
		{
			Comp->DestroyComponent();
		}
	}

	CachedCounterReferences.Reset();

	for (UStaticMeshComponent* MeshComponent : CharacterMeshes)
	{
		if (MeshComponent)
		{
			MeshComponent->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
			MeshComponent->SetStaticMesh(nullptr);
			MeshComponent->DestroyComponent();
		}
	}
	CharacterMeshes.Reset();

	for (USceneComponent* KerningComponent : CharacterKernings)
	{
		if (KerningComponent)
		{
			KerningComponent->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
			KerningComponent->DestroyComponent();
		}
	}
	CharacterKernings.Reset();
}

void UText3DComponent::BuildTextMesh(const bool bCleanCache)
{
	bPendingBuild = false;
	CheckBevel();

	// Clear previous glyphs and bounds
	ClearTextMesh();
	if (!Font)
	{
		return;
	}

	// Get font face
	UText3DEngineSubsystem* Subsystem = GEngine->GetEngineSubsystem<UText3DEngineSubsystem>();
	FCachedFontData& CachedFontData = Subsystem->GetCachedFontData(Font);
	FT_Face Face = CachedFontData.GetFreeTypeFace();
	if (!Face)
	{
		UE_LOG(LogText3D, Error, TEXT("Failed to load font data '%s'"), *CachedFontData.GetFontName());
		return;
	}

	CachedCounterReferences.Add(CachedFontData.GetCacheCounter());
	CachedCounterReferences.Add(CachedFontData.GetMeshesCacheCounter(bOutline, Extrude, Bevel, BevelType, BevelSegments));

	// Shape the text
	ShapedText->Reset();
	ShapedText->LineHeight = Face->size->metrics.height * FontInverseScale;
	ShapedText->FontAscender = Face->size->metrics.ascender * FontInverseScale;
	ShapedText->FontDescender = Face->size->metrics.descender * FontInverseScale;

	FTextShaper::Get()->ShapeBidirectionalText(Face, Text.ToString(), ShapedText->Lines);

	CalculateTextWidth();
	TextRoot->SetRelativeScale3D(GetTextScale());

	// ---------------- LAYOUT METRICS ----------------
	float LayoutMaxWidth = 0.f;
	for (const FShapedGlyphLine& Line : ShapedText->Lines)
	{
		LayoutMaxWidth = FMath::Max(LayoutMaxWidth, Line.Width);
	}
	const float LayoutHeight = GetTextHeight();

	// ---------------- TOP-LEFT PIVOT & COLLISION BOUNDS ----------------
	if (ShapedText->Lines.Num() > 0)
	{
		// Bounding box half-extents
		const FVector BoxExtent(
			Extrude * 0.5f,        // X = depth
			LayoutMaxWidth * 0.5f, // Y = width
			LayoutHeight * 0.5f    // Z = half height
		);

		// Move TextRoot pivot to top-left-front corner of bounding box
		TextRoot->SetRelativeLocation(FVector(
			0.f,                          // X = front face (no offset needed)
			0.f,                          // Y = left edge (no offset needed)
			-ShapedText->FontAscender     // Z = move down from baseline to top
		));

		// Create bounding box
		UBoxComponent* BoundsBox = NewObject<UBoxComponent>(this, TEXT("Text3D_Bounds"));
		BoundsBox->SetupAttachment(TextRoot);
		BoundsBox->RegisterComponent();
		GetOwner()->AddInstanceComponent(BoundsBox);
		BoundsBox->SetBoxExtent(BoxExtent);

		// Center box so top of first line aligns with top of box
		BoundsBox->SetRelativeLocation(FVector(
			Extrude * 0.5f,
			LayoutMaxWidth * 0.5f,
			ShapedText->FontAscender - LayoutHeight * 0.5f  // Correct center offset
		));

		// Enable collision
		BoundsBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		BoundsBox->SetCollisionObjectType(ECC_WorldDynamic);
		BoundsBox->SetCollisionResponseToAllChannels(ECR_Ignore);
		BoundsBox->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
		BoundsBox->SetCollisionResponseToChannel(ECC_Camera, ECR_Block);
		BoundsBox->SetGenerateOverlapEvents(true);
	}

	// ---------------- GLYPHS ----------------
	int32 GlyphIndex = 0;
	for (int32 LineIndex = 0; LineIndex < ShapedText->Lines.Num(); LineIndex++)
	{
		const FShapedGlyphLine& ShapedLine = ShapedText->Lines[LineIndex];
		FVector Location = GetLineLocation(LineIndex); // Top-left of this line relative to baseline

		for (int32 LineGlyph = 0; LineGlyph < ShapedLine.GlyphsToRender.Num(); LineGlyph++)
		{
			FVector GlyphLocation = Location;
			Location.Y += ShapedLine.GetAdvanced(LineGlyph, Kerning, WordSpacing);

			const FShapedGlyphEntry& ShapedGlyph = ShapedLine.GlyphsToRender[LineGlyph];
			if (!ShapedGlyph.bIsVisible)
			{
				continue;
			}

			UStaticMesh* CachedMesh = CachedFontData.GetGlyphMesh(
				ShapedGlyph.GlyphIndex, bOutline, Extrude, Bevel, BevelType, BevelSegments);

			if (!CachedMesh)
			{
				continue;
			}

			int32 GlyphId = GlyphIndex++;

			// Kerning component
			FString KerningName = FString::Printf(TEXT("CharachterKerning%d"), GlyphId);
			USceneComponent* CharKerning = NewObject<USceneComponent>(this, FName(*KerningName));

#if WITH_EDITOR
			CharKerning->SetIsVisualizationComponent(true);
#endif
			CharKerning->AttachToComponent(TextRoot, FAttachmentTransformRules::KeepRelativeTransform);
			CharKerning->RegisterComponent();
			CharacterKernings.Add(CharKerning);

			// Mesh component
			FString MeshName = FString::Printf(TEXT("StaticMeshComponent%d"), GlyphId);
			UStaticMeshComponent* StaticMesh = NewObject<UStaticMeshComponent>(this, FName(*MeshName));

#if WITH_EDITOR
			StaticMesh->SetIsVisualizationComponent(true);
#endif
			StaticMesh->SetStaticMesh(CachedMesh);
			StaticMesh->RegisterComponent();
			CharacterMeshes.Add(StaticMesh);

			StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			StaticMesh->SetCollisionResponseToAllChannels(ECR_Ignore);

			GetOwner()->AddInstanceComponent(StaticMesh);
			StaticMesh->AttachToComponent(CharKerning, FAttachmentTransformRules::KeepRelativeTransform);

			CharKerning->SetRelativeLocation(GlyphLocation);
		}
	}

	// ---------------- APPLY MATERIALS ----------------
	for (int32 Index = 0; Index < static_cast<int32>(EText3DGroupType::TypeCount); Index++)
	{
		EText3DGroupType Type = static_cast<EText3DGroupType>(Index);
		UpdateMaterial(Type, GetMaterial(Type));
	}

	TextGeneratedDelegate.Broadcast();

	if (bCleanCache)
	{
		Subsystem->Cleanup();
	}
}

void UText3DComponent::CheckBevel()
{
	if (Bevel > MaxBevel())
	{
		Bevel = MaxBevel();
	}
}

float UText3DComponent::MaxBevel() const
{
	return Extrude / 2.0f;
}

void UText3DComponent::UpdateMaterial(const EText3DGroupType Type, UMaterialInterface* Material)
{
	int32 Index = static_cast<int32>(Type);
	for (UStaticMeshComponent* StaticMeshComponent : CharacterMeshes)
	{
		StaticMeshComponent->SetMaterial(Index, Material);
	}
}

#undef LOCTEXT_NAMESPACE
