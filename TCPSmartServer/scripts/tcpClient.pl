#!/usr/bin/perl -w
 
use Getopt::Std;
use Socket;
 
# declare the perl command line flags/options we want to allow
my %options=();
getopts("hs:p:n:", \%options);
 
if ($options{h})
{
  do_help();
  exit 0;
}
 
if (!($options{s} && $options{p} && $options{n}))
{
  do_help();
  exit 0;
}

sub do_help {
  print "perl $0 -h [Help] -s [Server Ip Address] -p [Port Number] -n [Number of Request]";
  print "$0 will run with providing -s, -p and -n options."
}


$remote_host = $options{s};
$remote_port = $options{p};
$number_request = $options{n};

$message = "GETMESSAGE\n";
#$message = "BYE\n";
#$message = "ahcekllkjer\n";

use IO::Socket::INET;
 
# auto-flush on socket
$| = 1;
 
for (my $count = 0; $count < $number_request; $count++)
{
	# create a connecting socket
	my $socket = new IO::Socket::INET (
			PeerHost => $remote_host,
			PeerPort => $remote_port,
			Proto => 'tcp',
			);
	die "cannot connect to the server $!\n" unless $socket;
	print "connected to the server\n";

	# data to send to a server
	my $req = $message;
	my $size = $socket->send($req);
	print "Sent data: $message\n";

	# receive a response of up to 1024 characters from server
	my $response = "";
	$socket->recv($response, 100);
	print "Received response: $response\n";
	
	$socket->close();
}
