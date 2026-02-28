#include "StarcelHelper.h"
#include "Framework/Application/SlateApplication.h"
#include "GenericPlatform/GenericWindow.h"
#include "Input/Events.h"


// https://forums.unrealengine.com/t/how-to-inject-simulate-mouse-clicks/25602/7
void UStarcelHelper::ClickLMB()
{
	FSlateApplication& SlateApp = FSlateApplication::Get();
	FPointerEvent MouseDownEvent(
		0,
		SlateApp.CursorPointerIndex,
		SlateApp.GetCursorPos(),
		SlateApp.GetLastCursorPos(),
		SlateApp.GetPressedMouseButtons(),
		EKeys::LeftMouseButton,
		0,
		SlateApp.GetPlatformApplication()->GetModifierKeys()
	);
	TSharedPtr<FGenericWindow> GenWindow;
	SlateApp.ProcessMouseButtonDownEvent(GenWindow, MouseDownEvent);
}
