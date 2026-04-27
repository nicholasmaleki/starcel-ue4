#include "StarcelHelper.h"
#include "Framework/Application/SlateApplication.h"
#include "GenericPlatform/GenericWindow.h"
#include "Input/Events.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "UnrealClient.h"


// https://forums.unrealengine.com/t/how-to-inject-simulate-mouse-clicks/25602/7
// Post 7 (EstherZuidgeest, Apr 2019) — fires both code paths so a click
// reaches everything that cares: viewport InputKey for Blueprint /
// InputComponent LMB events, and Slate ProcessMouseButton* for UMG and
// editor-Slate widgets. A click is press + release, so both halves are sent.
void UStarcelHelper::ClickLMB()
{
	FSlateApplication& SlateApp = FSlateApplication::Get();

	FViewportClient* Client = nullptr;
	FViewport* Viewport = nullptr;
	if (GEngine && GEngine->GameViewport && GEngine->GameViewport->Viewport)
	{
		Viewport = GEngine->GameViewport->Viewport;
		Client = Viewport->GetClient();
	}

	// Press
	if (Client)
	{
		Client->InputKey(Viewport, 0, EKeys::LeftMouseButton, EInputEvent::IE_Pressed);
	}

	TSet<FKey> PressedButtons = SlateApp.GetPressedMouseButtons();
	PressedButtons.Add(EKeys::LeftMouseButton);

	FPointerEvent MouseDownEvent(
		0,
		SlateApp.CursorPointerIndex,
		SlateApp.GetCursorPos(),
		SlateApp.GetLastCursorPos(),
		PressedButtons,
		EKeys::LeftMouseButton,
		0,
		SlateApp.GetPlatformApplication()->GetModifierKeys()
	);
	TSharedPtr<FGenericWindow> GenWindow;
	SlateApp.ProcessMouseButtonDownEvent(GenWindow, MouseDownEvent);

	// Release
	if (Client)
	{
		Client->InputKey(Viewport, 0, EKeys::LeftMouseButton, EInputEvent::IE_Released);
	}

	PressedButtons.Remove(EKeys::LeftMouseButton);
	FPointerEvent MouseUpEvent(
		0,
		SlateApp.CursorPointerIndex,
		SlateApp.GetCursorPos(),
		SlateApp.GetLastCursorPos(),
		PressedButtons,
		EKeys::LeftMouseButton,
		0,
		SlateApp.GetPlatformApplication()->GetModifierKeys()
	);
	SlateApp.ProcessMouseButtonUpEvent(MouseUpEvent);
}
