
cd build/
cmake .. 
make -j4

openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000" -c "program tentacle-controller.elf verify reset exit"
