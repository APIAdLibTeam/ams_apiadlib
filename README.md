## ams_apiadlib

Drupal 7.x. wrapper module for APIAdLib library for using in set of AMS modules and other.

-   Contributors: pshentsoff
-   Donate link: https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=FGRFBSFEW5V3Y
-   Tags: APIAdLib, AMS, Yandex.Direct, Google.AdWords
-   Author: pshentsoff
-   Author's homepage: http://pshentsoff.ru
-   License: Apache License, Version 2.0
-   License URI: http://www.apache.org/licenses/LICENSE-2.0.html

### Version history

#### version 7.x-0.0.2-dev from 28.05.2012
-   container class AMSAPIAdLibSOAPClient
    -   save ams_auth property
    -   save soap_client property
    -   soap_client property set as default
-   functions moved apart from module
-   library now loads once - sign that library already loaded and checkin it
-   library use autoloads - ok
  
#### version 0.0.1-dev from 19.05.2012
-   library APIAdLib included as part of AMS APIAdLib module (not as third-party library as early)
-   loading library functions
-   creation main objects such as AdsUser, AdsSoapClient
-   simple testing routines (for Yandex.Direct only)
