//
// PROJECT:         Aspia Remote Desktop
// FILE:            ui/system_info/report_progress_dialog.h
// LICENSE:         Mozilla Public License Version 2.0
// PROGRAMMERS:     Dmitry Chapyshev (dmitry@aspia.ru)
//

#ifndef _ASPIA_UI__SYSTEM_INFO__REPORT_PROGRESS_DIALOG_H
#define _ASPIA_UI__SYSTEM_INFO__REPORT_PROGRESS_DIALOG_H

#include "base/macros.h"
#include "ui/resource.h"

#include <atlbase.h>
#include <atlapp.h>
#include <atlwin.h>
#include <atlmisc.h>

namespace aspia {

class ReportProgressDialog
    : public CDialogImpl<ReportProgressDialog>
{
public:
    enum { IDD = IDD_REPORT_PROGRESS };

    ReportProgressDialog() = default;
    ~ReportProgressDialog() = default;

private:
    BEGIN_MSG_MAP(ReportProgressDialog)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        COMMAND_ID_HANDLER(IDCANCEL, OnCancelButton)
    END_MSG_MAP()

    LRESULT OnInitDialog(UINT message, WPARAM wparam, LPARAM lparam, BOOL& handled);
    LRESULT OnCancelButton(WORD notify_code, WORD ctrl_id, HWND ctrl, BOOL& handled);

    DISALLOW_COPY_AND_ASSIGN(ReportProgressDialog);
};

} // namespace aspia

#endif // _ASPIA_UI__SYSTEM_INFO__REPORT_PROGRESS_DIALOG_H