.PHONY: clean All

All:
	@echo "----------Building project:[ TestFramework - Debug ]----------"
	@"$(MAKE)" -f  "TestFramework.mk"
clean:
	@echo "----------Cleaning project:[ TestFramework - Debug ]----------"
	@"$(MAKE)" -f  "TestFramework.mk" clean
