FROM ubuntu:22.04
RUN apt-get update && apt-get upgrade -y
RUN apt-get install -y build-essential python3 python3-pip wget unzip
RUN python3 -m pip install scons==4.4.0
WORKDIR /godot-tmp
ENV GODOT_VERSION=4.1.1
ENV GODOT_VERSION_SUFFIX=stable
RUN wget -O godot.zip "https://downloads.tuxfamily.org/godotengine/${GODOT_VERSION}/Godot_v${GODOT_VERSION}-${GODOT_VERSION_SUFFIX}_linux.x86_64.zip"
WORKDIR /godot
RUN unzip /godot-tmp/godot.zip && rm /godot-tmp/godot.zip && mv ./Godot_v${GODOT_VERSION}-${GODOT_VERSION_SUFFIX}_linux.x86_64 ./godot
RUN touch ./._sc_

WORKDIR /app
COPY . .
RUN scons -j$(nproc)