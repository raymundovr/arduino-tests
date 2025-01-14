if [ "$#" -ne 1 ]; then
    echo "Incorrect arguments. Missing target folder"
    exit 0
fi

# WARNING: a personal solution
PORT=$(arduino-cli board list --json | jq .detected_ports[0].port.address | tr -d '"')

# Compile and upload to device
arduino-cli compile --fqbn arduino:avr:mega $1
arduino-cli upload -p $PORT --fqbn arduino:avr:mega $1
