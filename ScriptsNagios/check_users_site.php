#!/usr/bin/php
<?php

try{
    $client= new SoapClient('http://wvm074.dei.isep.ipp.pt/LAPR5/WebService.svc?wsdl');
    $result=$client->getNumberUsers();
    $res = $result->getNumberUsersResult;
}catch(Exception $e){
    print "CRITICAL - WebService is not acessible. $e";
    exit(1);
}

if(file_exists('/tmp/users'))
{
        $ficheiro=fopen("/tmp/users","r");
        $str=fgets($ficheiro,100);
        fclose($ficheiro);
        
        $strInt = (int)$str;
        if($res != $strInt)
        {
            $ficheiro = fopen('/tmp/users','w');
            fputs($ficheiro,$res);
            fclose($ficheiro);
            print "WARNING - The number of users changed. Last: $strInt; Now: $res";
            exit(1);
        }else{
            fclose($ficheiro);
            print "OK - The number of users has not changed";
            exit(0);
        }
}else{
        $ficheiro = fopen('/tmp/users','w');
        fputs($ficheiro,$res);
        fclose($ficheiro);
        print "WARNING - No file found to compare. Add new file. Number of users now: $res";
        exit(1);
}
?>
