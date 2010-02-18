//
// This file is part of Condor2Nav file formats translator.
//
// Copyright (C) 2009 Mateusz Pusz
//
// Condor2Nav is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Condor2Nav is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Condor2Nav. If not, see <http://www.gnu.org/licenses/>.
//
// Visit the project webpage (http://sf.net/projects/condor2nav) for more info.
//

/**
* @file gui\main.cpp
*
* @brief Defines the entry point for the GUI application. 
*/

#include "stdafx.h"
#include "condor2navGUI.h"
#include "widgets.h"
#include "resource.h"
#include <exception>

static HINSTANCE hInst = 0;


// Message handler for about box.
INT_PTR CALLBACK AboutDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message) {
  case WM_INITDIALOG:
    return TRUE;

  case WM_COMMAND:
    if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
      EndDialog(hDlg, LOWORD(wParam));
      return TRUE;
    }
    break;
  }
  return FALSE;
}


INT_PTR CALLBACK MainDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  static condor2nav::gui::CCondor2NavGUI *app = 0;
  switch(message) {
  case WM_INITDIALOG:
    app = new condor2nav::gui::CCondor2NavGUI(hInst, hDlg);
    return TRUE;

  case WM_COMMAND:
    {
      int wmId = LOWORD(wParam);
      int wmEvent = HIWORD(wParam);
      switch(wmId) {
      // Parse the menu selections
      case IDM_ABOUT:
        DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hDlg, AboutDialogProc);
        return TRUE;
      case IDM_EXIT:
        DestroyWindow(hDlg);
        return TRUE;
      default:
        // Pass the command to MainDialog widgets
        app->Command(hDlg, wmId, wmEvent);
      }
    }
    return TRUE;

  case WM_CLOSE:
    delete app;
    DestroyWindow(hDlg);
    return TRUE;

  case WM_DESTROY:
    PostQuitMessage(0);
    return TRUE;
  }
  return FALSE;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, char *cmdParam, int cmdShow)
{
  try
  {
    hInst = hInstance;

    // init RichEdit controls
    LoadLibrary("RichEd20.dll");

    // create MainDialog window
    HWND hDialog = CreateDialog(hInst, MAKEINTRESOURCE(IDD_MAIN_DIALOG), NULL, (DLGPROC)MainDialogProc);
    if(!hDialog)
      throw condor2nav::EOperationFailed("Unable to create main application dialog (error: " + condor2nav::Convert(GetLastError()) + ")!!!");

    // process application messages
    MSG msg;
    int status;
    while((status = GetMessage(&msg, NULL, 0, 0)) != 0) {
      if(status == -1)
        return EXIT_FAILURE;
      if(!IsDialogMessage(hDialog, &msg)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    }
    
    return msg.wParam;
  }
  catch(const condor2nav::Exception &ex)
  {
    MessageBox(0, ex.what(), "Condor2Nav Exception", MB_ICONEXCLAMATION | MB_OK);
  }
  catch(const std::exception &ex)
  {
    MessageBox(0, ex.what(), "Exception", MB_ICONEXCLAMATION | MB_OK);
  }
  catch(...)
  {
    MessageBox(0, "Unknown", "Exception", MB_ICONEXCLAMATION | MB_OK);
  }
  
  return EXIT_FAILURE;
}