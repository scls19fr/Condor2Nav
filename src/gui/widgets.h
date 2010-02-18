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
* @file gui\widgets.h
*
* @brief Declares the widgets classes. 
*/

#ifndef __WIDGETS_H__
#define __WIDGETS_H__

namespace condor2nav {

  namespace gui {

    class CWidget {
      const HWND _hWnd;
      CWidget(const CWidget &);
      CWidget &operator=(const CWidget &);
    public:
      CWidget(HWND hwndParent, int id, bool disabled = false);
      void Focus() const;
      void Enable() const;
      void Disable() const;
      HWND Hwnd() const;
    };


    class CWidgetButton : public CWidget {
    public:
      CWidgetButton(HWND hwndParent, int id, bool disabled = false);
    };


    //class CWidgetCheckBox : public CWidgetButton
    //{
    //public:
    //  CWidgetCheckBox(HWND hwndParent, int id, bool disabled = false)
    //    : CWidgetButton(hwndParent, id, disabled)
    //  {}
    //  bool Checked() const
    //  {
    //    return(SendMessage(Hwnd(), BM_GETCHECK, 0, 0) == BST_CHECKED);
    //  }
    //  void Check()
    //  {
    //    SendMessage(Hwnd(), BM_SETCHECK, (WPARAM) BST_CHECKED, 0);
    //  }
    //  void UnCheck() 
    //  {
    //    SendMessage(Hwnd(), BM_SETCHECK, (WPARAM) BST_UNCHECKED, 0);
    //  }
    //};


    class CWidgetRadioButton : public CWidgetButton {
    public:
      CWidgetRadioButton(HWND hwndParent, int id, bool disabled = false);
      bool Selected() const;
      void Select() const;
    };


    class CWidgetEdit : public CWidget {
    public:
      CWidgetEdit(HWND hwndParent, int id, bool disabled = false);
      void String(const std::string &str) const;
      std::string String() const;

      //// code is the HIWORD (wParam)
      //static bool Changed(int code)
      //{
      //  return code == EN_CHANGE;
      //}

      //void Select()
      //{
      //  SendMessage (Hwnd(), EM_SETSEL, 0, -1);
      //}

      //void ClearSelection ()
      //{
      //  SendMessage (Hwnd(), EM_SETSEL, -1, 0);
      //}
    };


    class CWidgetComboBox : public CWidget {
    public:
      CWidgetComboBox(HWND hwndParent, int id, bool disabled = false);
      void Add(const std::string &str) const;
      std::string Selection() const;
      bool ItemSelected() const;
    };


    class CWidgetRichEdit : public CWidget {
    public:
      enum TColor {
        COLOR_AUTO,
        COLOR_RED,
        COLOR_GREEN,
        COLOR_BLUE,
        COLOR_BLACK
      };

      enum TEffect {
        EFFECT_BOLD   = 0x01,
        EFFECT_ITALIC = 0x02,
      };

      CWidgetRichEdit(HWND hwndParent, int id, bool disabled = false);
      void Clear();
      void Format(unsigned effectMask, TColor color);
      void Append(const std::string &text);
    };

  } // namespace gui

} // namespace condor2nav


inline HWND condor2nav::gui::CWidget::Hwnd() const
{
  return _hWnd;
}


#endif // __WIDGETS_H__