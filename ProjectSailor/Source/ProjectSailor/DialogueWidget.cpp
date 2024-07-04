// Property of DaPaRy Games


#include "DialogueWidget.h"


void UDialogueWidget::UpdateText(const FText& NewText)
{
	if (TextDialogue)
	{
		TextDialogue->SetText(NewText);
	}
}

void UDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();

	
	if (DialogueImage)
	{
		
	}

	if (TextDialogue)
	{
		
	}
}
