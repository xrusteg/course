project_code:
	$(MAKE) -C ./day1
	$(MAKE) -C ./day2
	$(MAKE) -C ./day3
clean:
	$(MAKE) -C ./day1 clean
	$(MAKE) -C ./day2 clean
	$(MAKE) -C ./day3 clean
