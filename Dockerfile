FROM gcc:latest

RUN mkdir /app
COPY . /app
WORKDIR /app

RUN set -ex; \
    apt-get update; \
    apt-get install -y --no-install-recommends \
        valgrind \
        time \
        pandoc \
    ; \
    rm -rf /var/lib/apt/lists/*;

RUN g++ -std=c++17 main.cpp -o app

RUN chmod +x run.sh
ENTRYPOINT ["./run.sh"]
