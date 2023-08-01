#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDrawing.generated.h"

UCLASS()
class MYPROJECT_API ACDrawing : public AActor {
    GENERATED_BODY()

public:
    ACDrawing();

    UFUNCTION(BlueprintCallable, Category = "Drawing")
    void DrawLine(FVector Start, FVector End, FLinearColor Color, float Thickness = 1.0f);

    UFUNCTION(BlueprintCallable, Category = "Drawing")
    void DrawRectangle(FVector2D TopLeft, FVector2D BottomRight, FLinearColor Color, float Thickness = 1.0f, bool bFilled = false);

    UFUNCTION(BlueprintCallable, Category = "Drawing")
    void DrawPolygon(const TArray<FVector2D>& Vertices, FLinearColor Color, float Thickness = 1.0f, bool bFilled = false);

    UFUNCTION(BlueprintCallable, Category = "Drawing")
    void DrawText(FVector2D Position, const FText& Text, UFont* Font, FLinearColor Color, float Scale = 1.0f, bool bBold = false, bool bItalic = false);

    UFUNCTION(BlueprintCallable, Category = "Drawing")
    FVector2D GetTextSize(const FText& Text, UFont* Font, float Scale = 1.0f, bool bBold = false, bool bItalic = false);
};

#include "CDrawing.h"
#include "Engine/Canvas.h"

ACDrawing::ACDrawing() {
    PrimaryActorTick.bCanEverTick = true;
}

void ACDrawing::DrawLine(FVector Start, FVector End, FLinearColor Color, float Thickness) {
    // 画线段的实现
}

void ACDrawing::DrawRectangle(FVector2D TopLeft, FVector2D BottomRight, FLinearColor Color, float Thickness, bool bFilled) {
    // 画矩形的实现
}

void ACDrawing::DrawPolygon(const TArray<FVector2D>& Vertices, FLinearColor Color, float Thickness, bool bFilled) {
    // 画多边形的实现
}

void ACDrawing::DrawText(FVector2D Position, const FText& Text, UFont* Font, FLinearColor Color, float Scale, bool bBold, bool bItalic) {
    // 画文本的实现
}

FVector2D ACDrawing::GetTextSize(const FText& Text, UFont* Font, float Scale, bool bBold, bool bItalic) {
    // 获取文本尺寸的实现
    return FVector2D(); // 返回一个示例向量，需要在实际实现中计算实际尺寸
}
