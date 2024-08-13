#!/usr/bin/perl
use lib '/Users/hael-mou/Desktop/webserv/_pages/cgi-bin/auth/lib';
use strict;
use warnings;
use CGI;
use File::Slurp;
use Session;

my $cgi = CGI->new();
my $method = $ENV{'REQUEST_METHOD'} || 'GET';
my $session_id = $cgi->cookie('session_id');
my %users = (
	'admin' => 'admin',
);

if ($session_id)
{
	print $cgi->redirect(
		-url => '/web/home.pl',
		-status => '302 Temporary Redirect',
	);
	exit;
}

if ($method ne 'POST') {
	print $cgi->header( -type => 'text/html' );
	print read_file('public/sign_in.html');
	exit;
}

my $username = $cgi->param('username') || '';
my $password = $cgi->param('password') || '';

if (!exists $users{$username} || $users{$username} ne $password) {
	print $cgi->header( -type => 'text/html' );
	print "<script>alert('Wrong username or password.')</script>";
	print read_file('public/sign_in.html');
	exit;
}

my $session = Session->new();
$session->set('username', $username);
$session->set('password', $password);

print $cgi->redirect(
	-url => '/web/home.pl',
	-status => '302 Temporary Redirect',
	-cookie => $session->generate_cookie(),
);
