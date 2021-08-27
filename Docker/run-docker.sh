if [ $# -ne 1 ]; then
    echo "Usage: $0 <OmnetDevelopmentDir>"
    exit 1
fi


SCRIPT_DIR="$(realpath "$(dirname "$0")")"
DOCKER_SOCKET="/var/run/socker.sock"

HOST_XAUTH="$SCRIPT_DIR/Xauthority"
DOCKER_XAUTH="/home/omnetpp/Xauthority"

XSOCK="/tmp/.X11-unix"

DOCKER_OMNETFEDERATE_DIR="/home/omnetpp/workspace/OmnetFederate"

HOST_MAIN_DIR="$(realpath "$SCRIPT_DIR/../foundation/OmnetFederate/src/main")"
DOCKER_MAIN_DIR="$DOCKER_OMNETFEDERATE_DIR/CPSWT/main"

HOST_HLA_DIR="$(realpath "$SCRIPT_DIR/../foundation/OmnetFederate/src/hla")"
DOCKER_HLA_DIR="$DOCKER_OMNETFEDERATE_DIR/CPSWT/hla"

HOST_PROJECT_DIR="$(realpath "$1")"
DOCKER_PROJECT_DIR="$DOCKER_OMNETFEDERATE_DIR/Project"


touch "$HOST_XAUTH"
xauth nlist :0 | sed -e 's/^..../ffff/' | xauth -f "$HOST_XAUTH" nmerge -
docker run -it --rm -v "$XSOCK":"$XSOCK" -v "$HOST_XAUTH":"$DOCKER_XAUTH" \
  -v "$HOST_MAIN_DIR":"$DOCKER_MAIN_DIR" -v "$HOST_HLA_DIR":"$DOCKER_HLA_DIR" -v "$HOST_PROJECT_DIR:$DOCKER_PROJECT_DIR" \
  -e XAUTHORITY="$DOCKER_XAUTH" -e DISPLAY="$DISPLAY" --name omnetfederate omnetfederate bash

rm -r "$HOST_XAUTH"

