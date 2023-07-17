FROM gcc:9.5
ARG APP_NAME='NumberSorter.cpp'
WORKDIR /app
COPY $APP_NAME /app
COPY IntegerNumbersToBeSorted.txt /app
RUN g++ -std=c++17 $APP_NAME -lpthread -o NumberSorter
CMD ["./NumberSorter"]
