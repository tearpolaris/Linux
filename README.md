http://www.fpgadeveloper.com/2014/07/creating-a-base-system-for-the-zynq-in-vivado.html
 
http://www.fpgadeveloper.com/2014/08/creating-a-custom-ip-block-in-vivado.html

https://reactos.org/

http://usbip.sourceforge.net/#documentation

https://lwn.net/Articles/449509/

https://pdfs.semanticscholar.org/c7c4/cb054d75810fdb0a2affa11c288b7687267f.pdf

https://bootlin.com/docs/

https://docs.microsoft.com/en-us/windows/win32/winsock/complete-client-code

https://drive.google.com/file/d/1te6WUcKBFHNJN5ORVpYXtTPjyDfXFbp4/view?usp=sharing

https://www.vn-z.vn/redirect?to=aHR0cHM6Ly9kcml2ZS5nb29nbGUuY29tL2RyaXZlL2ZvbGRlcnMvMEI0ZlU1X19WWGtJa05tdEJRVzlmUkUxcGVEQQ==

https://drive.google.com/drive/folders/0B4fU5__VXkIkNmtBQW9fRE1peDA

    
foreach set_id("typical" "maximum")
    foreach bus_width("1024" "512" "256" "128" "64" "32" "16" "8")
        foreach gcc ("6.3" "4,8")
            foreach timing_mode ("lt" "at") 
                foreach axi_type("axi3" "axi4") 
                    foreach input_clock("true" "false")
                        foreach output_clock("true" "false")
                            if ($bus_width =~ "1024") then
                                if ($gcc =~ "6.3") && ($timing_mode =~ "lt") then
                                    
                                endif
                                  
                                if ($axi_type =~ "axi3") && ($input !~ "true") && ($output_clock !~ "true")
                                    #ignore 
                                endif
                            else if ($bus_width =~ "512") 
                                 #ignore
                            else if ($bus_width =~ "256")
                                 #ignore
                            else if ($bus_width =~ "128")
                                if ($axi_type =~ "axi3") && ($input !~ "true") && ($output_clock !~ "true")
                                    #ignore
                                    
                                endif
    
                                if ($gcc =~ "4.8") then
                                    if ($timing_mode !~ "at") then
                                        #ignore
                                    endif
                                    if (($input_clock !~ "true") && ($output_clock !~ "true")) then
                                        #ignore
                                    endif
    
                                else
                                    if ($timing_mode !~ "lt") then
                                       #ignore
                                    endif
                                    if (($input_clock !~ "true") && ($output_clock !~ "false")) then
                                       #ignore
                                    endif
                                endif
                            else if ($bus_width =~ "64")
                                if ($gcc =~ "4.8") then
                                    #ignore
                                endif
                                if ($timing_mode =~ "at") then
                                    if (($axi_type =~ "axi3") && ($input_clock !~ "true") && ($output_clock !~ "false")) then
                                        #ignore
                                    endif
                                    if (($axi_type =~ "axi4") && ($input_clock !~ "false") && ($output_clock !~ "true") then
                                       #ignore
                                    endif
                                else
                                    if (($input_clock !~ "false") && ($output_clock !~ "true")) then
                                       #ignore
                                    endif
                                endif
                                   
                            else if ($bus_width =~ "32")
                                if ($gcc =~ "4.8") then
                                    #ignore
                                endif
    
                                if ($timing_mode =~ "at") then
                                    if (($axi_type =~ "axi3") && ($input_clock !~ "false") && ($output_clock !~ "true")) then
                                        #ignore
                                    endif
                                    if (($axi_type =~ "axi4") && ($input_clock !~ "true") && ($output_clock !~ "false") then
                                       #ignore
                                    endif
                                else
                                    if (($axi_type =~ "axi3") && ($input_clock !~ "true") && ($output_clock !~ "false")) then
                                        #ignore
                                    endif
                                    if (($axi_type =~ "axi4") && ($input_clock !~ "true") && ($output_clock !~ "true") then
                                       #ignore
                                    endif
                                endif
                            else if ($bus_width =~ "8")
                                if ($gcc =~ "4.8") then
                                    #ignore
                                endif
    
                                if ($timing_mode =~ "at") then
                                    if (($input_clock !~ "true") && ($output_clock !~ "true") then
                                       #ignore
                                    endif
                                else
                                    if (($axi_type =~ "axi3") && ($input_clock !~ "true") && ($output_clock !~ "true")) then
                                        #ignore
                                    endif
                                    if (($axi_type =~ "axi4") && ($input_clock !~ "true") && ($output_clock !~ "false") then
                                       #ignore
                                    endif
                                endif
                            endif
                            source ./frun_gen_list $bus_width $axi_type $timing_mode $gcc $input_clock $output_clock $set_id $en_coverage $run_sim
                        end
                    end
                end
            end
        end
    end
end
