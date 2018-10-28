FROM gcc:latest

RUN mkdir /app
COPY . /app
WORKDIR /app

RUN apt-get update
RUN apt-get install -y valgrind
RUN apt-get install -y time 

RUN g++ -std=c++17 main.cpp -o app

RUN chmod +x run.sh
ENTRYPOINT ["./run.sh"]
