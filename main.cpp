#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#define MAX_CHECKBOXES 12
#include "../raygui.h"
#include "stdio.h"

static void DrawChecklist();
static void UpdateChecklist();

const int screenWidth = 600;
const int screenHeight = 600;

float yCheckBox = 0;
float xCheckBox = 100;

char textBoxText[128] = "\0";

// Array to store text for each checkbox
char checkBoxTexts[MAX_CHECKBOXES][128]; 

// Array to store the checked state for each checkbox
bool checkedStates[MAX_CHECKBOXES] = { false };

int boxCounter = 0;

int main(){
    InitWindow(screenWidth, screenHeight, "checklist");
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        UpdateChecklist();
        DrawChecklist();
    }
    CloseWindow();
    return 0;
}

void DrawChecklist()
{
    BeginDrawing();
        ClearBackground(RAYWHITE);
    EndDrawing();
}

void UpdateChecklist()
{
    Rectangle TextBoxRec = {150, 560, 300, 30};
    GuiTextBox(TextBoxRec, textBoxText, 128, true);
    Rectangle AddButtonRec = {470, 560, 100, 30};
    
    if (GuiButton(AddButtonRec, "Add") && boxCounter < MAX_CHECKBOXES){
        // Copy the current text box content to the next checkbox text
        strcpy(checkBoxTexts[boxCounter], textBoxText);
        // Increment the counter for the number of checkboxes
        boxCounter++;

        sprintf(textBoxText, "\0");
    }

    if(IsKeyPressed(KEY_ENTER) && boxCounter < MAX_CHECKBOXES){
        // Copy the current text box content to the next checkbox text
        strcpy(checkBoxTexts[boxCounter], textBoxText);
        // Increment the counter for the number of checkboxes
        boxCounter++;

        sprintf(textBoxText, "\0");
    }

    for (int i = 0; i < boxCounter; i++){
        Rectangle CheckBoxRec = {30,static_cast<float>(20 + i * 40), 30, 30};
        GuiCheckBox(CheckBoxRec, checkBoxTexts[i], &checkedStates[i]);
        Rectangle RemoveButtonRec = {490,static_cast<float>(20 + i * 40), 60, 30};

        if(GuiButton(RemoveButtonRec, "Remove")){
            for(int j = i; j < boxCounter - 1; j++){
                // Copies the text of deleted checkbox [j], to the next checkbox [j + 1]
                strcpy(checkBoxTexts[j], checkBoxTexts[j + 1]);

                //Copies the chckedState bool from the deleted one [j], to the next checkbox [j + 1]
                checkedStates[j] = checkedStates[j + 1];
            }
            boxCounter--;
        }
    }
}
