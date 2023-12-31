# Create a virtual environment with all tools installed
# ref: https://hub.docker.com/_/fedora
FROM fedora:latest AS env

# Install system build dependencies
ENV PATH=/usr/local/bin:$PATH
RUN dnf -y update \
&& dnf -y install git wget \
&& dnf -y groupinstall "Development Tools" \
&& dnf -y install gcc-c++ zlib-devel \
&& dnf -y install dnf-plugins-core \
&& dnf -y copr enable vbatts/bazel \
&& dnf -y install which \
&& dnf clean all

# Install Bazelisk
RUN wget \
https://github.com/bazelbuild/bazelisk/releases/download/v1.17.0/bazelisk-linux-amd64 \
&& chmod +x bazelisk-linux-amd64 \
&& mv bazelisk-linux-amd64 /usr/local/bin/bazel

# Install Python
RUN dnf -y update \
&& dnf -y install python3 python3-devel python3-pip \
&& dnf clean all

FROM env AS devel
WORKDIR /home/project
COPY . .

FROM devel AS build
RUN bazel version
RUN bazel build \
 -c opt \
 --cxxopt="-std=c++17" \
 --subcommands=true \
 ...

FROM build AS test
# bazel5 struggle to find any python[3] interpreter in PATH even if available
# i.e. @rules_python//python:autodetecting_toolchain is broken
RUN bazel test \
 -c opt \
 --cxxopt="-std=c++17" \
 --test_output=errors \
 ...
