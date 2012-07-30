#!/usr/bin/perl

$uname = qx(uname);
chomp($uname);

$hostname = qx(hostname);
chomp($hostname);

if ( $ENV{'OS'} eq "Windows_NT" )	{
	if ( $ENV{'COMPUTERNAME'} eq "LAFAMIGLIA" ) {
		#chdir "D:\\Sorgenti\\Perl";
	} else {
		print " Not on LaFamiglia. Exiting.\n";
		exit();
	}
} elsif ( $uname eq "Linux" ) {

	if ( $hostname eq "PESTODURO" ) {
		chdir "/home/waleviolaeivan/Sorgenti/FantaCalcGuiNew/src";
		$revision = qx(git rev-parse HEAD);	
		chomp($revision);	
		system("sed 's/XXX/$revision/g' revision.h.in > revision.h");
	} else {
		print " Not on Pestoduro. Exiting.\n";
		exit();	
	}
} else {
	print " System not recognized. Exiting.\n";
	exit();
}


