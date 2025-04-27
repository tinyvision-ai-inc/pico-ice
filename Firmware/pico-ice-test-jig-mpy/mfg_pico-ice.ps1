$DeviceId = $null
echo "Insert Boot mode pico-ice and remove the jumper"
while ($DeviceId -eq  $null) {
	Start-Sleep -Seconds 1
	$DeviceId = Get-WmiObject Win32_logicaldisk| ? {$_.DriveType -eq 2} | Select-Object -Property DeviceId
	$DeviceId = $DeviceId.DeviceId
}
echo "Flashing..."
Copy-Item "pico_ice.uf2" -Destination $DeviceId
echo "Done, Waiting Until Disk shows up again, You may need to unplug and re-plug the device if windows decided so"
Start-Sleep -Seconds 2

#$DeviceId = $null
#while ($DeviceId -eq  $null) {
#	Start-Sleep -Seconds 1
#	$DeviceId = Get-WmiObject Win32_logicaldisk| ? {$_.DriveType -eq 2} | Select-Object -Property DeviceId
#	$DeviceId = $DeviceId.DeviceId
#}
echo "Copying test.bit"
mpremote cp test_pico_ice.bit :test.bit
Start-Sleep -Seconds 1

echo "Running tests"
mpremote run run_tests_rp2040.py
if($?) {
	echo "Tests Successful... Deleting files and flashing factory FPGA firmware"
	mpremote rm :test.bit
	mpremote cp final.bit :
	Start-Sleep -Seconds 1
	mpremote run flash_final_rp2040.py
	mpremote rm :final.bit
	mpremote cp main_rp2040.py :main.py
}
else
{
	echo "*** Tests failed! ***"
}
