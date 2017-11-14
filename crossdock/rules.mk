XDOCK_YAML=crossdock/docker-compose.yml

JAEGER_COMPOSE_URL=https://raw.githubusercontent.com/jaegertracing/jaeger/master/docker-compose/jaeger-docker-compose.yml
XDOCK_JAEGER_YAML=crossdock/jaeger-docker-compose.yml

.PHONY: crossdock
crossdock: crossdock-download-jaeger
	docker-compose -f $(XDOCK_YAML) -f $(XDOCK_JAEGER_YAML) kill cpp
	docker-compose -f $(XDOCK_YAML) -f $(XDOCK_JAEGER_YAML) rm -f cpp
	docker-compose -f $(XDOCK_YAML) -f $(XDOCK_JAEGER_YAML) build cpp
	docker-compose -f $(XDOCK_YAML) -f $(XDOCK_JAEGER_YAML) run crossdock 2>&1 | tee run-crossdock.log
	grep 'Tests passed!' run-crossdock.log

.PHONY: crossdock-fresh
crossdock-fresh: crossdock-download-jaeger
	docker-compose -f $(XDOCK_JAEGER_YAML) -f $(XDOCK_YAML) kill
	docker-compose -f $(XDOCK_JAEGER_YAML) -f $(XDOCK_YAML) rm --force
	docker-compose -f $(XDOCK_JAEGER_YAML) -f $(XDOCK_YAML) pull
	docker-compose -f $(XDOCK_JAEGER_YAML) -f $(XDOCK_YAML) build
	docker-compose -f $(XDOCK_JAEGER_YAML) -f $(XDOCK_YAML) run crossdock

.PHONY: crossdock-logs
crossdock-logs: crossdock-download-jaeger
	docker-compose -f $(XDOCK_JAEGER_YAML) -f $(XDOCK_YAML) logs

.PHONY: crossdock-download-jaeger
crossdock-download-jaeger:

