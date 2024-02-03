#include "Helper.h"

UHelper::UHelper()
{
}

UHelper::~UHelper()
{
}

FVector UHelper::GetMousePos()
{
    return GEngine->MainWindow.GetMousePosition();
}