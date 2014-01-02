#include <windows.h>
#include "resource.h"

const char g_szClassName[] = "myWindowClass";

#define ID_FILE_EXIT        9001
#define ID_STUFF_MODELESS   9002
#define ID_STUFF_GO         9003
#define ID_STUFF_ABOUT      9004

HWND g_modelessHwnd;

BOOL CALLBACK AboutProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{

    switch ( msg )
    {
    case WM_INITDIALOG:
        break;
    case WM_COMMAND:
        switch ( LOWORD( wParam ) )
        {
        case IDOK:
            EndDialog( hwnd, IDOK );
            break;
        case IDCANCEL:
            EndDialog( hwnd, IDCANCEL );
            break;
        }
        break;
    default:
        return FALSE;
    }

    return TRUE;
}

BOOL CALLBACK ModelessDlgProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch ( msg )
    {
    case WM_COMMAND:
        switch ( LOWORD( wParam ) )
        {
        case IDC_BUTTON1:
            MessageBox( hwnd, "Yes man", "Yes", MB_OK | MB_ICONINFORMATION );
            break;
        case IDC_BUTTON2:
            MessageBox( hwnd, "Baby's first word", "No", MB_OK | MB_ICONINFORMATION );
            break;
        }
        break;
    default:
        return FALSE;
    }

    return TRUE;
}

/* Get menu bar */
HMENU GetMenuBar()
{
    HMENU hmenu = CreateMenu();

    HMENU hfilepopup = CreateMenu();
    AppendMenu( hfilepopup, MF_STRING, ID_FILE_EXIT, "E&xit" );
    AppendMenu( hmenu, MF_STRING | MF_POPUP, ( UINT ) hfilepopup, "&File" );

    HMENU hstuffpopup = CreateMenu();
    AppendMenu( hstuffpopup, MF_STRING, ID_STUFF_MODELESS, "&Modeless Dialog" );
    AppendMenu( hstuffpopup, MF_STRING, ID_STUFF_GO, "&Go" );
    AppendMenu( hstuffpopup, MF_STRING, ID_STUFF_ABOUT, "&About" );
    AppendMenu( hmenu, MF_STRING | MF_POPUP, ( UINT ) hstuffpopup, "&Stuff" );

    return hmenu;
}

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch ( msg )
    {
    case WM_LBUTTONDOWN:
    {
        char szFileName[ MAX_PATH ];
        HINSTANCE hInstance = GetModuleHandle( NULL );
        GetModuleFileName( hInstance, szFileName, MAX_PATH );
        MessageBox( hwnd, szFileName, "The Program is: ", MB_OK | MB_ICONINFORMATION );
        break;
    }
    case WM_COMMAND:
        switch ( LOWORD( wParam ) )
        {
        case ID_FILE_EXIT:
            PostMessage( hwnd, WM_CLOSE, 0, 0 );
            break;
        case ID_STUFF_MODELESS:
        {
            g_modelessHwnd = CreateDialog( GetModuleHandle( NULL ), MAKEINTRESOURCE( IDD_DIALOG2 ), hwnd, ModelessDlgProc );
            if ( g_modelessHwnd != NULL )
            {
                ShowWindow( g_modelessHwnd, SW_SHOW );
            }
            else
            {
                MessageBox( hwnd, "Failed to open modeless dialog box!", "Error!", MB_OK | MB_ICONERROR );
            }
            break;
        }
        case ID_STUFF_GO:
            MessageBox( hwnd, "Stuff Go Menu Dialog Box", "GO", MB_OK | MB_ICONINFORMATION );
            break;
        case ID_STUFF_ABOUT:
            INT_PTR ret = DialogBox( GetModuleHandle( NULL ), MAKEINTRESOURCE( IDD_DIALOG1 ), hwnd, AboutProc );
            if ( ret <= 0 )
            {
                MessageBox( hwnd, "Dialog box errored out!", "Dialog box error", MB_OK | MB_ICONERROR );
            }
            break;
        }
        break;
    case WM_CLOSE:
        DestroyWindow( hwnd );
        break;
    case WM_DESTROY:
        DestroyWindow( g_modelessHwnd );
        PostQuitMessage( 0 );
        break;
    default:
        return DefWindowProc( hwnd, msg, wParam, lParam );
    }

    return 0;
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;

    wc.cbSize = sizeof( WNDCLASSEX );
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground = ( HBRUSH ) ( COLOR_WINDOW + 1 );
    wc.lpszMenuName = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm = LoadIcon( NULL, IDI_APPLICATION );

    if ( !RegisterClassEx( &wc ) )
    {
        MessageBox( NULL, "Window registration failed", "ERROR!", MB_ICONEXCLAMATION | MB_OK );
        return 0;
    }

    hwnd = CreateWindowEx( WS_EX_CLIENTEDGE, g_szClassName, "Simple Window Title", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 512, 256, NULL, GetMenuBar(), hInstance, NULL );

    if ( hwnd == NULL )
    {
        MessageBox( NULL, "Window creation failed", "ERROR!", MB_ICONEXCLAMATION | MB_OK );
        return 0;
    }

    ShowWindow( hwnd, nCmdShow );
    UpdateWindow( hwnd );

    while ( GetMessage( &msg, NULL, 0, 0 ) > 0 )
    {
        if ( IsDialogMessage( g_modelessHwnd, &msg ) )
        {
            continue;
        }
        TranslateMessage( &msg );
        DispatchMessage( &msg );
    }

    return 0;
}
