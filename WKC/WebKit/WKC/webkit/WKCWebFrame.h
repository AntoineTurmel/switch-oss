/*
 *  WKCWebFrame.h
 *
 *  Copyright (c) 2010-2017 ACCESS CO., LTD. All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 * 
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 * 
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the
 *  Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 *  Boston, MA  02110-1301, USA.
 */

#ifndef WKCWebFrame_h
#define WKCWebFrame_h

// class definition

#include "WKCEnums.h"
#include "WKCClientBuilders.h"
#include "WKCFaviconInfo.h"

#ifdef WKC_ENABLE_CUSTOMJS
#include <wkc/wkccustomjs.h>
#endif // WKC_ENABLE_CUSTOMJS

#include <JavaScriptCore/JavaScript.h>

namespace WKC {
    class Frame;
    class HTMLFrameOwnerElement;
    class ResourceRequest;
}

namespace WKC {

/*@{*/

class WKCWebViewPrivate;
class WKCWebFramePrivate;
class WKCWebDataSource;
class WKCSecurityOrigin;

/** @brief Class that corresponds to frames */
class WKC_API WKCWebFrame
{
public:
    /**
       @brief Generates WKC::WKCWebFrame instance.
       @param view Pointer to WKC::WKCWebView instance
       @param builders Reference to WKC::WKCClientBuilders instance
       @retval Pointer to WKC::WKCWebFrame instance
       @details
       Creates WKC::WKCWebFrame instance and returns its pointer as a return value.
       @attention
       WKC::WKCWebFrame must be called to discard the generated WKC::WKCWebFrame::deleteWKCWebFrame() instance.
    */
    static WKCWebFrame* create(WKCWebView* view, WKCClientBuilders& builders);
    /**
       @brief Generates WKC::WKCWebFrame instance.
       @param view Pointer to WKC::WKCWebViewPrivate instance
       @param builders Reference to WKC::WKCClientBuilders instance
       @param ownerelement Pointer to owner element
       @param ismainframe frame is mainframe or not
       @retval Pointer to WKC::WKCWebFrame instance
       @details
       Creates WKC::WKCWebFrame instance and returns its pointer as a return value.
       @attention
       WKC::WKCWebFrame must be called to discard the generated WKC::WKCWebFrame::deleteWKCWebFrame() instance.
    */
    static WKCWebFrame* create(WKCWebViewPrivate* view, WKCClientBuilders& builders, WKC::HTMLFrameOwnerElement* ownerelement=0, bool ismainframe=false);
    /**
       @brief Discards WKC::WKCWebFrame instance.
       @param self Pointer to WKC::WKCWebFrame instance
       @return None
       @details
       Discards the WKC::WKCWebFrame instance generated by WKC::WKCWebFrame::create().
    */
    static void deleteWKCWebFrame(WKCWebFrame* self);

    /**
       @brief Notifies of forced termination of WKC::WKCWebFrame.
       @return None
       @details
       Notifies of the forced termination of the WKC::WKCWebFrame instance generated by WKC::WKCWebFrame::create().
    */
    void notifyForceTerminate();

    // APIs
    /**
       @brief Gets WKC::Frame instance.
       @retval Pointer to WKC::Frame instance
    */
    WKC::Frame* core() const;
    /**
       @brief Compares WKC::Frame instance.
       @param self Pointer to WKC::Frame instance
       @retval "!= false" True
       @retval "== false" False
    */
    bool compare(const WKC::Frame* self) const;

    /**
       @brief Gets WKC::WKCWebView instance.
       @retval Pointer to WKC::WKCWebView instance
    */
    WKCWebView* webView();
    /**
       @brief Gets name
       @retval "const unsigned short*" Pointer to name string
    */
    const unsigned short* name();
    /**
       @brief Gets title
       @retval "const unsigned short*" Pointer to title string
    */
    const unsigned short* title();
    /**
       @brief Gets URI
       @retval "const char*" Pointer to URI string
    */
    const char* uri();
    /**
       @fn  WKCWebFrame* WKC::WKCWebFrame::parent()
       @brief Gets parent WKC::WKCWebFrame instance.
       @retval Pointer to parent WKC::WKCWebFrame instance
    */
    WKCWebFrame* parent();

    /**
       @brief Starts loading page
       @param uri Pointer to URI string
       @param referrer Referer
       @return None
    */
    void loadURI(const char* uri, const char* referrer = 0);
    /**
       @brief Displays content string
       @param content Pointer to content string
       @param mime_type Pointer to mime type string
       @param encoding Pointer to encoding type string
       @param base_uri Pointer to base URI string
       @param unreachable_uri Pointer to error content URI string
       @param replace Replace current document
       @return None
    */
    void loadString(const char* content, const unsigned short* mime_type, const unsigned short* encoding, const char *base_uri, const char *unreachable_uri=0, bool replace = false);
    /**
       @brief Starts loading page
       @param request Loading request
       @return None
    */
    void loadRequest(const WKC::ResourceRequest& request);
    /**
       @brief Stops loading page
       @return None
    */
    void stopLoading();
    /**
       @brief Reloads page
       @return None
    */
    void reload();

    /**
       @brief Searches frame
       @param name Pointer to name string
       @retval Pointer to WKC::WKCWebFrame instance
    */
    WKCWebFrame* findFrame(const unsigned short* name);

    JSGlobalContextRef globalContext();

    /**
       @brief Gets WKC::LoadStatus enum value indicating page status
       @retval WKC::LoadStatus enum value
    */
    WKC::LoadStatus loadStatus();
    /**
       @brief Gets WKC::ScrollbarMode enum value indicating horizontal scroll bar setting status
       @retval WKC::ScrollbarMode enum value
    */
    WKC::ScrollbarMode horizontalScrollbarMode();
    /**
       @brief Gets WKC::ScrollbarMode enum value indicating vertical scroll bar setting status
       @retval WKC::ScrollbarMode enum value
    */
    WKC::ScrollbarMode verticalScrollbarMode();

    /**
       @brief Gets WKCSecurityOrigin
       @retval WKCSecurityOrigin
    */
    WKCSecurityOrigin* securityOrigin();
    /**
       @brief Gets Favicon URL
       @retval Other than 0 Pointer to Favicon URL string (NULL terminated)
       @retval 0 Favicon does not exist
    */
    const char* faviconURL();
    /**
       @brief Gets favicon information
       @param info Pointer to WKC::WKCFaviconInfo_ structure
       @param in_reqwidth request width
       @param in_reqheight request height
       @retval "!= false" Succeeded
       @retval "== false" Favicon does not exist
       @details
       The application gets favicon information by calling this API when FrameLoaderClientWKC::dispatchDidReceiveIcon occurs.@n
       And, the application must allocate memory, for the members that require memory allocation (fIconData, fIconBmpData, and fIconBmpMask), in the WKC::WKCFaviconInfo_ structure.@n
       Therefore, this API must be called two times.@n
       On the first call, the application gets information related to various memory sizes, then after allocating the required memory ranges it calls this a second time.@n
       For details of the required memory range size information, see WKC::WKCFaviconInfo_.@n
       @attention
       Before the first call to this API, the WKC::WKCFaviconInfo_ structure members must be 0 initialized.
    */
    bool getFaviconInfo(WKCFaviconInfo* info, int in_reqwidth=16, int in_reqheight=16);

    // pagesave
    /**
       @brief Starts page saving process
       @retval "!= false" Succeeded
       @retval "== false" Failed
       @details
       If WKC::WKCWebFrame::contentSerializeStart fails, do not call WKC::WKCWebFrame::contentSerializeProgress.
    */
    bool contentSerializeStart();
    /**
       @brief Serializes saved page data
       @param buffer Pointer to buffer that stores serialized data (memory must be allocated on application side)
       @param length Buffer size
       @retval >0 If buffer==0, it returns the memory size required to save pages.@n
       If buffer!=0, copies data required to save pages, and returns the size (bytes) of copied data.
       @retval ==0 Serialization completed
       @retval <0 Serialization failed
       @details
       Stores serialized saved page data in buffer, and returns that size as the return value.
       The saved page data can be output to a file, divided into buffer units, by calling this API until a return value of 0 is returned.
    */
    int contentSerializeProgress(void* buffer, unsigned int length);
    /**
       @brief Completes page saving process.
       @return None
       @details
       When the return value of WKC::WKCWebFrame::contentSerializeProgress is ==0 or 0, call this API to complete the page saving process.
    */
    void contentSerializeEnd();
    /**
       @brief Checks whether error occurred in saved page loading process.
       @retval "!= false" Error occurred
       @retval "== false" Error did not occur, or there is no saved page loading process
       @details
       When the notification of WKC::FrameLoaderClientWKC::dispatchDidFinishLoad is given, the application calls this API to check if an error occurred while reading saved pages, and if an error has occurred, the application must go to the next transition history item.
    */
    bool isPageArchiveLoadFailed();

#ifdef WKC_ENABLE_CUSTOMJS
    bool setCustomJSAPIList(const int listnum, const WKCCustomJSAPIList *list);
    bool setCustomJSAPIListInternal(const int listnum, const WKCCustomJSAPIList *list);
    bool setCustomJSStringAPIList(const int listnum, const WKCCustomJSAPIList *list);
    bool setCustomJSStringAPIListInternal(const int listnum, const WKCCustomJSAPIList *list);

    WKCCustomJSAPIList* getCustomJSAPI(const char* api_name);
    WKCCustomJSAPIList* getCustomJSAPIInternal(const char* api_name);
    WKCCustomJSAPIList* getCustomJSStringAPI(const char* api_name);
    WKCCustomJSAPIList* getCustomJSStringAPIInternal(const char* api_name);

    void setForcedSandboxNavigation();
#endif // WKC_ENABLE_CUSTOMJS
    void executeScript(const char* script);

    /**
       @brief Pause or restart JavaScripts executions.
       @param pause 
       - !=false pause
       - ==false restart
       @return None
       @details
       Pauses execution of JavaScripts or re-start it again.
    */
    void setJavaScriptPaused(bool pause);
    /**
       @brief Get the pausing state of JavaScript execution.
       @retval "!= false" pausing
       @retval "== false" running
       @details
       Returns JavaScript pausing state.
    */
    bool isJavaScriptPaused() const;
    /**
       @brief Suspend animations.
       @return None
       @details
       Suspend animations.
    */
    void suspendAnimations();
    /**
       @fn void WKC::WKCWebFrame::resumeAnimations()
       @brief Resume animations.
       @return None
       @details
       Resumes animations.
    */
    void resumeAnimations();

    /**
       @fn void WKC::WKCWebFrame::setSpatialNavigationEnabled()
       @brief Enable / disable spatial navigation
       @param enable 
       - !=false enable
       - ==false disable
       @return None
       @details
       Enable / disable spatial navigation.
    */
    void setSpatialNavigationEnabled(bool enable);

private:
    WKCWebFrame();
    ~WKCWebFrame();
    bool construct(WKCWebViewPrivate* view, WKCClientBuilders& builders, WKC::HTMLFrameOwnerElement* ownerelement, bool ismainframe);

    friend class WKCWebViewPrivate;
    friend class ChromeClientWKC;
    friend class FrameLoaderClientWKC;
    inline WKCWebFramePrivate* privateFrame() const { return m_private; }

private:
    WKCWebFramePrivate* m_private;
};

/*@}*/

} // namespace

#endif // WKCWebFrame_h
