// 2024/6/21 11:40:13 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Communicator/HTTP/HTTP.h"
#include "Frame.h"


namespace HTTP
{
    static const wxString url = "https://wltech.ru/wifi/post-data-mst.php";
    static const wxString content_type = "application/x-www-form-urlencoded";
    static const wxString key = "api_key=PtmAT51b3j4F8";
}


void HTTP::SendPOST(TypeMeasure::E, float value)
{
    wxWebRequest request = wxWebSession::GetDefault().CreateRequest(Frame::self, url);

    Frame::self->Bind(wxEVT_WEBREQUEST_STATE, &Frame::OnWetRequestState, Frame::self);

    wxString body = "api_key=PtmAT51b3j4F8&value1=24.75&value2=54.27&value3=994.01&meas_time = 2024-06-17 16:45:29";

    request.SetData(body, content_type);

    request.Start();
}
