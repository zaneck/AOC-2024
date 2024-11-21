DAY = $(subst run-,,$@)

.PHONY: %

%:
	bash Day-$(DAY)/run.sh
