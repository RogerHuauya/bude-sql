#pragma once

#include <cstring>
#include <string>
#include <iostream>
#include <raylib.h>
#include "../src/proxy/proxy.h"

class QueryVisual {
public:
    QueryVisual(QueryResult A) {
        this->Visual = std::move(A);
        scrollOffset = 0;
    }

    void Update() {
        // Handle scrolling input
        int wheelMove = GetMouseWheelMove();
        scrollOffset -= wheelMove * lineSpacing; // Adjust scroll speed if needed

        // Clamp scrollOffset to prevent scrolling out of bounds
        int maxOffset = std::max(0, static_cast<int>(Visual.records.size()) * lineSpacing - (rectHeight - textPadding - 2 * lineSpacing));
        if (scrollOffset < 0) scrollOffset = 0;
        if (scrollOffset > maxOffset) scrollOffset = maxOffset;
    }

    void Render() {
        const int rectX = GetScreenWidth() - rectWidth - 110;
        const int rectY = 85;

        // Draw the background rectangle
        DrawRectangle(rectX, rectY, rectWidth, rectHeight, LIGHTGRAY);

        // Set the initial position for the text
        int textPosX = rectX + textPadding;
        int textPosY = rectY + textPadding;

        // Draw column headers (these should stay static)
        for (const auto &column : Visual.columns) {
            DrawText(column.c_str(), textPosX, textPosY, 20, BLACK);
            textPosX += columnSpacing;
        }

        // Draw a line to separate headers from data
        textPosY += lineSpacing;
        DrawLine(rectX + textPadding, textPosY, rectX + rectWidth - textPadding, textPosY, BLACK);

        // Reset text position for data
        textPosX = rectX + textPadding;

        // Draw records, adjusted by the scroll offset
        textPosY += lineSpacing; // Start drawing data below the header line
        for (const auto &record : Visual.records) {
            int currentTextPosY = textPosY - scrollOffset; // Adjust position by scroll offset
            if (currentTextPosY > rectY + lineSpacing && currentTextPosY < rectY + rectHeight) {
                textPosX = rectX + textPadding;
                for (const auto &column : Visual.columns) {
                    DrawText(record[column].c_str(), textPosX, currentTextPosY, 20, DARKGRAY);
                    textPosX += columnSpacing;
                }
            }
            textPosY += lineSpacing;
        }

        //std::cout << Visual << std::endl;
    }

private:
    QueryResult Visual;
    int scrollOffset;
    const int rectWidth = 1100;
    const int rectHeight = 600;
    const int textPadding = 10;
    const int lineSpacing = 20;
    const int columnSpacing = 70;
};
