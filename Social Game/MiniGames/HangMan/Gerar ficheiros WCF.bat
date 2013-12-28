echo off

SET OUTPUT_PATH=WCF
SET WSDL=http://localhost:8733/Design_Time_Addresses/SocialGameService/Service1/?wsdl

RD /s /q %OUTPUT_PATH%
MD %OUTPUT_PATH%
CD %OUTPUT_PATH%

"C:\Program Files (x86)\Microsoft SDKs\Windows\v8.1A\bin\NETFX 4.5.1 Tools\svcutil.exe" /t:metadata %WSDL%
"C:\Program Files (x86)\Windows Kits\8.1\bin\x86\wsutil.exe" *.xsd *.wsdl
pause