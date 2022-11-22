param($day)
  
if ($day -eq $null) {
  $day = (Get-Date).Day
}

while ( (Get-Date).Hour -lt 7 ) {
  Write-Output "zzZ"
  Start-Sleep -Seconds 5
}
$downloadToPath = "..\inputs\Day$day\input.txt"
if (!(Test-Path "..\inputs\Day$day")) {
  New-Item -Path "..\inputs\" -name "Day$day" -ItemType "directory" 
}
$remoteFileLocation = "https://adventofcode.com/2021/day/$day/input"
  
$session = New-Object Microsoft.PowerShell.Commands.WebRequestSession
    
$cookie = New-Object System.Net.Cookie 
    
$cookie.Name = "session"
$cookie.Value = $env:AOC_SESSION
$cookie.Domain = ".adventofcode.com"

$session.Cookies.Add($cookie);

Invoke-WebRequest $remoteFileLocation -WebSession $session -TimeoutSec 900 -OutFile $downloadToPath

Write-Output "Got input for day $day"