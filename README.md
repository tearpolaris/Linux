# Linux
reslx.bus_shwy_32		set_addrmap	0xFFF93000	0xFFF94FFF    1
reslx.bus_shwy_32		set_addrmap	0xFFF95000	0xFFF96FFF    2

1 	GUISCXML 	Free 	https://github.com/fmorbini/scxmlgui 	Need IT evaluation if apply this tool
2 	Qt Creator 	Free/License 	https://www.qt.io/download 	Standard Software of IT
3 	QSFM 	Free 	http://qfsm.sourceforge.net/ 	Need IT evaluation if apply this tool
4   Commons SCXM

https://www.digikey.com/eewiki/display/LOGIC/Xilinx+Vivado+Design+Suite+-+Getting+Started


<scxml initial="SyncMode" name="SCI3State" version="1.0"><!--   node-size-and-position x=0 y=0 w=750 h=945  -->
 <parallel id="AsyncMode"><!--   node-size-and-position x=160 y=330 w=560 h=340  -->
  <onentry>SCI3AsyncSendState-&gt;Start()
SCI3AsyncReceiveState-&gt;Start()</onentry>
  <onexit>SCI3AsyncSendState-&gt;End()
SCI3AsyncReceiveState-&gt;End()</onexit>
  <transition event="Reset" target="Reset"><!--   edge-path [Reset]  x=80 y=300 pointx=0 pointy=16 offsetx=1 offsety=-1  --></transition>
  <transition event="Writing10SMA_CA" target="SyncMode"><!--   edge-path [SyncMode]  x=300 y=250 pointx=0 pointy=9 offsetx=-3 offsety=-44  --></transition>
  <state id="SCI3AsyncSendState" initial="IDLE"><!--   node-size-and-position x=20 y=50 w=280 h=250  -->
   <state id="IDLE"><!--   node-size-and-position x=33 y=80 w=75 h=75  -->
    <transition event="Start" target="WaitTDRE"><!--   edge-path [WaitTDRE]  x=130 y=90 pointx=0 pointy=9 offsetx=6 offsety=-3  --></transition>
   </state>
   <state id="WaitTDRE"><!--   node-size-and-position x=150 y=80 w=75 h=75  -->
    <transition target="IDLE"><!--   edge-path [IDLE]  x=130 y=150  --></transition>
   </state>
  </state>
  <state id="SCI3AsyncReceiveState"><!--   node-size-and-position x=320 y=50 w=230 h=250  --></state>
 </parallel>
 <state id="Reset"><!--   node-size-and-position x=20 y=168 w=75 h=75  -->
  <transition event="DeassertReset" target="AsyncMode"><!--   edge-path [AsyncMode]  x=100 y=290 pointx=0 pointy=23 offsetx=-5 offsety=-2  --></transition>
 </state>
 <state id="SyncMode"><!--   node-size-and-position x=150 y=40 w=570 h=140  -->
  <onentry>SCI3SyncState-&gt;Start()</onentry>
  <onexit>SCI3SyncState-&gt;End()</onexit>
  <transition event="Reset" target="Reset"></transition>
  <transition event="Writing0SMA_CA" target="AsyncMode"><!--   edge-path [AsyncMode]  x=520 y=240 pointx=0 pointy=0 offsetx=10 offsety=0  --></transition>
  <state id="SCI3SyncState"><!--   node-size-and-position x=30 y=40 w=290 h=80  --></state>
 </state>
</scxml>
