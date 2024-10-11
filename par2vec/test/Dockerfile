# Use the official Ubuntu 20.04 as the base image
FROM ubuntu:20.04

# Set environment variable to prevent user interaction during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Update the package list and install dependencies for building Python from source
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    software-properties-common \
    build-essential \
    wget \
    libssl-dev \
    zlib1g-dev \
    libbz2-dev \
    libreadline-dev \
    libsqlite3-dev \
    curl \
    libncurses5-dev \
    libncursesw5-dev \
    xz-utils \
    tk-dev \
    libffi-dev \
    liblzma-dev \
    python3-pip \
    python3-setuptools \
    python3-dev

# Install Python manually
RUN apt-get install -y python3.9 python3.9-dev python3.9-venv

# Set Python 3.8 as the default version of Python
RUN update-alternatives --install /usr/bin/python3 python3 /usr/bin/python3.9 1 && \
    update-alternatives --install /usr/bin/python python /usr/bin/python3.9 1

# Verify the installation
RUN python3 --version && pip3 --version

RUN pip install torch torchvision torchaudio --index-url https://download.pytorch.org/whl/cpu
RUN pip install transformers sentence-transformers
RUN pip install googletrans==4.0.0rc1

# Set a working directory
WORKDIR /app
COPY ./comp-sim.py .

RUN pip install grpcio-tools
COPY ./par2vec_pb2_grpc.py .
COPY ./par2vec_pb2.py .
COPY ./par2vec_pb2.pyi .
COPY ./main.py .

EXPOSE 50052


# Clean up the cache to reduce the image size
#RUN apt-get clean && \
#    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*



# Add a command to keep the container running or use it interactively
#CMD ["python3"]
CMD ["python main.py"]
