.PHONY: clean All

All:
	@echo "----------Building project:[ emulator_in_c - Debug ]----------"
	@"$(MAKE)" -f  "emulator_in_c.mk"
clean:
	@echo "----------Cleaning project:[ emulator_in_c - Debug ]----------"
	@"$(MAKE)" -f  "emulator_in_c.mk" clean
