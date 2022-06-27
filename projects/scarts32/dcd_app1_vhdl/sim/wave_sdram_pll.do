onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -radix hexadecimal /tbtbddcd_app1_design/dut/scarts_reset
add wave -noupdate /tbtbddcd_app1_design/clk
add wave -noupdate /tbtbddcd_app1_design/gdb_tx
add wave -noupdate /tbtbddcd_app1_design/gdb_rx
add wave -noupdate -expand -group SPI /tbtbddcd_app1_design/spi_cs(0)
add wave -noupdate -expand -group SPI /tbtbddcd_app1_design/spi_cs(1)
add wave -noupdate -expand -group SPI /tbtbddcd_app1_design/spi_cs(2)
add wave -noupdate -expand -group SPI /tbtbddcd_app1_design/spi_miso
add wave -noupdate -expand -group SPI /tbtbddcd_app1_design/spi_mosi
add wave -noupdate -expand -group SPI /tbtbddcd_app1_design/spi_clk
add wave -noupdate -radix hexadecimal /tbtbddcd_app1_design/spi_flash_addr
add wave -noupdate -group brom_unit /tbtbddcd_app1_design/dut/escarts32/brom_unit/clk
add wave -noupdate -group brom_unit /tbtbddcd_app1_design/dut/escarts32/brom_unit/hold
add wave -noupdate -group brom_unit -radix hexadecimal /tbtbddcd_app1_design/dut/escarts32/brom_unit/addr
add wave -noupdate -group brom_unit -radix hexadecimal -subitemconfig {/tbtbddcd_app1_design/dut/escarts32/brom_unit/data(15) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/brom_unit/data(14) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/brom_unit/data(13) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/brom_unit/data(12) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/brom_unit/data(11) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/brom_unit/data(10) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/brom_unit/data(9) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/brom_unit/data(8) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/brom_unit/data(7) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/brom_unit/data(6) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/brom_unit/data(5) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/brom_unit/data(4) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/brom_unit/data(3) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/brom_unit/data(2) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/brom_unit/data(1) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/brom_unit/data(0) {-radix hexadecimal}} /tbtbddcd_app1_design/dut/escarts32/brom_unit/data
add wave -noupdate -group iram_unit -radix hexadecimal -subitemconfig {/tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/wdata(15) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/wdata(14) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/wdata(13) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/wdata(12) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/wdata(11) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/wdata(10) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/wdata(9) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/wdata(8) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/wdata(7) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/wdata(6) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/wdata(5) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/wdata(4) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/wdata(3) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/wdata(2) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/wdata(1) {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/wdata(0) {-radix hexadecimal}} /tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/wdata
add wave -noupdate -group iram_unit -radix hexadecimal /tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/waddr
add wave -noupdate -group iram_unit /tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/wen
add wave -noupdate -group iram_unit -radix hexadecimal /tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/raddr
add wave -noupdate -group iram_unit -radix hexadecimal /tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/rdata
add wave -noupdate -group sdram -radix hexadecimal /tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/raddr
add wave -noupdate -group sdram -subitemconfig {/tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/r.curr_row {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/r.raddr_latch {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/r.rdata_latch {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/r.waddr_latch {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/r.wdata_latch {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/r.addr {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/r.dq {-radix hexadecimal}} -expand /tbtbddcd_app1_design/dut/escarts32/use_prog_gen/iram_unit/r
add wave -noupdate -group sdram /tbtbddcd_app1_design/dram_ba
add wave -noupdate -group sdram -radix hexadecimal -subitemconfig {/tbtbddcd_app1_design/dram_addr(12) {-radix hexadecimal} /tbtbddcd_app1_design/dram_addr(11) {-radix hexadecimal} /tbtbddcd_app1_design/dram_addr(10) {-radix hexadecimal} /tbtbddcd_app1_design/dram_addr(9) {-radix hexadecimal} /tbtbddcd_app1_design/dram_addr(8) {-radix hexadecimal} /tbtbddcd_app1_design/dram_addr(7) {-radix hexadecimal} /tbtbddcd_app1_design/dram_addr(6) {-radix hexadecimal} /tbtbddcd_app1_design/dram_addr(5) {-radix hexadecimal} /tbtbddcd_app1_design/dram_addr(4) {-radix hexadecimal} /tbtbddcd_app1_design/dram_addr(3) {-radix hexadecimal} /tbtbddcd_app1_design/dram_addr(2) {-radix hexadecimal} /tbtbddcd_app1_design/dram_addr(1) {-radix hexadecimal} /tbtbddcd_app1_design/dram_addr(0) {-radix hexadecimal}} /tbtbddcd_app1_design/dram_addr
add wave -noupdate -group sdram -radix hexadecimal -subitemconfig {/tbtbddcd_app1_design/dram_dq(15) {-radix hexadecimal} /tbtbddcd_app1_design/dram_dq(14) {-radix hexadecimal} /tbtbddcd_app1_design/dram_dq(13) {-radix hexadecimal} /tbtbddcd_app1_design/dram_dq(12) {-radix hexadecimal} /tbtbddcd_app1_design/dram_dq(11) {-radix hexadecimal} /tbtbddcd_app1_design/dram_dq(10) {-radix hexadecimal} /tbtbddcd_app1_design/dram_dq(9) {-radix hexadecimal} /tbtbddcd_app1_design/dram_dq(8) {-radix hexadecimal} /tbtbddcd_app1_design/dram_dq(7) {-radix hexadecimal} /tbtbddcd_app1_design/dram_dq(6) {-radix hexadecimal} /tbtbddcd_app1_design/dram_dq(5) {-radix hexadecimal} /tbtbddcd_app1_design/dram_dq(4) {-radix hexadecimal} /tbtbddcd_app1_design/dram_dq(3) {-radix hexadecimal} /tbtbddcd_app1_design/dram_dq(2) {-radix hexadecimal} /tbtbddcd_app1_design/dram_dq(1) {-radix hexadecimal} /tbtbddcd_app1_design/dram_dq(0) {-radix hexadecimal}} /tbtbddcd_app1_design/dram_dq
add wave -noupdate -group sdram /tbtbddcd_app1_design/dram_clk
add wave -noupdate /tbtbddcd_app1_design/clk
add wave -noupdate /tbtbddcd_app1_design/dram_ctrl_str
add wave -noupdate -divider CORE
add wave -noupdate -radix hexadecimal /tbtbddcd_app1_design/dut/escarts32/core_unit/prog_cnt
add wave -noupdate -radix hexadecimal /tbtbddcd_app1_design/dut/escarts32/core_unit/iramo_rdata
add wave -noupdate -radix hexadecimal /tbtbddcd_app1_design/dut/escarts32/core_unit/bromo_data
add wave -noupdate -subitemconfig {/tbtbddcd_app1_design/dut/escarts32/core_unit/r.f -expand /tbtbddcd_app1_design/dut/escarts32/core_unit/r.f.pcnt {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/core_unit/r.f.jmpdest {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/core_unit/r.fd -expand /tbtbddcd_app1_design/dut/escarts32/core_unit/r.fd.pcnt {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/core_unit/r.d -expand /tbtbddcd_app1_design/dut/escarts32/core_unit/r.d.dec -expand /tbtbddcd_app1_design/dut/escarts32/core_unit/r.d.pcnt {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/core_unit/r.d.vectabaddr {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/core_unit/r.d.regfaddr1 {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/core_unit/r.d.regfaddr2 {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/core_unit/r.e -expand /tbtbddcd_app1_design/dut/escarts32/core_unit/r.e.result {-radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/core_unit/r.e.regfaddr {-radix unsigned} /tbtbddcd_app1_design/dut/escarts32/core_unit/r.w -expand /tbtbddcd_app1_design/dut/escarts32/core_unit/r.w.result {-radix hexadecimal}} -expand /tbtbddcd_app1_design/dut/escarts32/core_unit/r
add wave -noupdate -subitemconfig {/tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(0) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(1) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(2) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(3) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(4) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(5) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(6) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(7) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(8) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(9) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(10) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(11) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(12) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(13) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(14) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(15) {-height 15 -radix hexadecimal}} -expand -subitemconfig {/tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(0) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(1) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(2) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(3) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(4) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(5) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(6) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(7) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(8) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(9) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(10) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(11) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(12) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(13) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(14) {-height 15 -radix hexadecimal} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram(15) {-height 15 -radix hexadecimal}} /tbtbddcd_app1_design/dut/escarts32/regf_unit/ram1/ram
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 5} {8752173913 ps} 0} {{Cursor 2} {2004256353 ps} 0}
configure wave -namecolwidth 440
configure wave -valuecolwidth 148
configure wave -justifyvalue left
configure wave -signalnamewidth 1
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ms
update
WaveRestoreZoom {0 ps} {22050 us}
