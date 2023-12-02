FROM debian:bullseye-slim as base

USER root

#runtime dependencies
RUN apt update && apt --no-install-recommends -y install python3-pip python3 libpython3-dev curl net-tools

#Libs required in runtime
RUN apt --no-install-recommends -y install file libboost-system-dev libboost-filesystem-dev libboost-program-options-dev libglib2.0-0 nlohmann-json3-dev libwebsocketpp-dev tini

#Installing python runtime deps for sc-machine
RUN python3 -m pip install --no-cache-dir termcolor tornado websocket-client


#Derived from debian and not "base" image because any change in base would cache bust the build environment
FROM debian:bullseye-slim AS buildenv
ENV CCACHE_DIR=/ccache
#Install build-time deps
RUN apt update && apt -y install git file libglib2.0-dev ccache libboost-system-dev libboost-filesystem-dev libboost-program-options-dev make cmake antlr gcc g++ llvm libcurl4-openssl-dev libclang-dev curl python3-dev python3-pip nlohmann-json3-dev libwebsocketpp-dev

## copy sources
WORKDIR /scn-editor
COPY . .

#Building sc-machine
RUN --mount=type=cache,target=/ccache/ cmake -B build && cmake --build build -j$(nproc)

#Gathering all artifacts together
FROM base AS final
COPY --from=buildenv /scn-editor/scn-editor.ini /scn-editor/scn-editor.ini
COPY --from=buildenv /scn-editor/kb /scn-editor/kb
COPY --from=buildenv /scn-editor/bin /scn-editor/bin
COPY --from=buildenv /scn-editor/problem-solver/sc-machine/scripts /scn-editor/problem-solver/sc-machine/scripts

EXPOSE 8090

ENTRYPOINT ["/usr/bin/tini", "--", "/scn-editor/problem-solver/sc-machine/scripts/docker_entrypoint.sh"]
CMD ["serve"]
