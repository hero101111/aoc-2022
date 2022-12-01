param($day, $year)

[bool] $crtDay = $false
if ($day -eq $null) 
{
  $day = (Get-Date).Day
  $crtDay = $true
}
if ($year -eq $null)
{
  $year = (Get-Date).Year
}

if ($crtDay)
{
  while ( (Get-Date).Hour -lt 7 ) {
    Write-Output "zzZ for year $year day $day"
    Start-Sleep -Seconds 5
  }
}
$downloadToPath = "..\inputs\Day$day\input.txt"
if (!(Test-Path "..\inputs\Day$day")) {
  New-Item -Path "..\inputs\" -name "Day$day" -ItemType "directory" 
}
$remoteFileLocation = "https://adventofcode.com/$year/day/$day/input"
  
$session = New-Object Microsoft.PowerShell.Commands.WebRequestSession
    
$cookie = New-Object System.Net.Cookie 
    
$cookie.Name = "session"
$cookie.Value = $env:AOC_SESSION
$cookie.Domain = ".adventofcode.com"
$session.Headers.Add("User-Agent", [System.Web.HttpUtility]::UrlEncode($env:AOC_EMAIL))

$session.Cookies.Add($cookie);

Invoke-WebRequest $remoteFileLocation -WebSession $session -TimeoutSec 900 -OutFile $downloadToPath

Write-Output "Got input for year $year day $day into path $downloadToPath"