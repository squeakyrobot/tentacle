
cd build/
# cmake clean
cmake .. # -DPICO_BOARD=tentacle_controller
# make clean
make -j16

openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000" -c "program tentacle-controller.elf verify reset exit"
