/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * The contents of this file are subject to the Netscape Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/NPL/
 *
 * Software distributed under the License is distributed on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * rights and limitations under the License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is Netscape
 * Communications Corporation.  Portions created by Netscape are
 * Copyright (C) 1999 Netscape Communications Corporation. All
 * Rights Reserved.
 *
 * Contributor(s): 
 */
#include "prprf.h"
#include "prmem.h"
#include "nsCOMPtr.h"
#include "nsString.h"
#include "nsIStringBundle.h"
#include "nsLocalStringBundle.h"
#include "nsIServiceManager.h"
#include "nsIURI.h"

/* This is the next generation string retrieval call */
static NS_DEFINE_CID(kStringBundleServiceCID, NS_STRINGBUNDLESERVICE_CID);

#define LOCAL_MSGS_URL       "chrome://messenger/locale/localMsgs.properties"

nsLocalStringService::nsLocalStringService()
{
  NS_INIT_ISUPPORTS();
}

nsLocalStringService::~nsLocalStringService()
{}

NS_IMPL_ADDREF(nsLocalStringService);
NS_IMPL_RELEASE(nsLocalStringService);

NS_INTERFACE_MAP_BEGIN(nsLocalStringService)
   NS_INTERFACE_MAP_ENTRY_AMBIGUOUS(nsISupports, nsIMsgStringService)
   NS_INTERFACE_MAP_ENTRY(nsIMsgStringService)
NS_INTERFACE_MAP_END

NS_IMETHODIMP 
nsLocalStringService::GetStringByID(PRInt32 aStringID, PRUnichar ** aString)
{
  nsresult rv = NS_OK;
  
  if (!mLocalStringBundle)
    rv = InitializeStringBundle();

  NS_ENSURE_TRUE(mLocalStringBundle, NS_ERROR_UNEXPECTED);
  NS_ENSURE_SUCCESS(mLocalStringBundle->GetStringFromID(aStringID, aString), NS_ERROR_UNEXPECTED);

  return rv;
}

NS_IMETHODIMP
nsLocalStringService::GetBundle(nsIStringBundle **aResult)
{
  NS_ENSURE_ARG_POINTER(aResult);
  nsresult rv = NS_OK;
  if (!mLocalStringBundle)
    rv = InitializeStringBundle();
  NS_ENSURE_SUCCESS(rv, rv);

  *aResult = mLocalStringBundle;
  NS_IF_ADDREF(*aResult);
  return NS_OK;
}

nsresult
nsLocalStringService::InitializeStringBundle()
{
  nsresult rv;
  nsCOMPtr<nsIStringBundleService> stringService = do_GetService(kStringBundleServiceCID, &rv);
  NS_ENSURE_SUCCESS(rv, rv);
  NS_ENSURE_TRUE(stringService, NS_ERROR_FAILURE);

  rv = stringService->CreateBundle(LOCAL_MSGS_URL, getter_AddRefs(mLocalStringBundle));
  return rv;
}

