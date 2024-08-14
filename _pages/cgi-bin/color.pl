#!/usr/bin/perl

use strict;
use warnings;
use CGI;

# Create CGI object
my $cgi = CGI->new();

# get Cookies:
my $color = $cgi->cookie('color');
unless ($cgi->cookie('color'))
{
	$color = 'yellow';
	print $cgi->header(
		-type => 'text/html',
		-cookie => $cgi->cookie(-name => 'color',
							    -value => $color,
								-path => '/cgi-bin/color.pl'
					)
	);
}
else
{
	print $cgi->header(-type => 'text/html');
}

print <<HTML;
<!DOCTYPE html>
<html>
<head>
	<title> hello World </title>
	<style>
		body
		{ 
			background-color: $color; 
			display: flex;
  			justify-content: center;
  			align-items: center;
  			height: 200px;
  			border: 3px solid green;
			margin: auto;
  			width: 50%;
  			margin-top: 35px;
		}
	</style>
	<script>
		function changeColor(color) {
			document.body.style.backgroundColor = color;
			document.cookie = "color=" + color + "; path=/cgi-bin/color.pl";
		}
	</script>
</head>
<body>
	<h1> select a color : </h1>
	<input type="color" value="$color" onchange="changeColor(this.value)">
</html>
HTML
