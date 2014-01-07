#!/usr/bin/php
<?php

try{
    $client= new SoapClient('http://wvm074.dei.isep.ipp.pt/LAPR5/WebService.svc?wsdl');
    $result=$client->getNumberDownloads();
    $res = $result->getNumberDownloadsResult;
    
}catch(Exception $e){
    print "CRITICAL - WebService is not acessible. $e";
    exit(2);
}
        if($res > 5 && $res < 100)
        {
            print "WARNING - Number of downloads: $res";
            exit(1);
        }elseif($res >= 100){
            print "CRITICAL - Number of downloads: $res";
            exit(2);
        }else{
            print "OK - Number of downloads: $res";
            exit(0);
        }
            
        
?>
