cd $(dirname $0)

# TO PUT include DIRECTORIES IN INCLUDE-DIRECTORY PATH LIST
INCLUDES=($(find . -iname "include" | while read path; do echo -n "-I$path "; done))

# TO PUT messages AND messages PARENT DIRECTORIES IN INCLUDE-DIRECTORY PATH LIST
INCLUDES+=($(find . -iname "messages" | while read path; do echo -n "-I$path -I$(dirname "$path") "; done))

opp_makemake -f -i var_mods.make -e cpp -P. --deep -O out -o OmnetFederate -KINET4_PROJ="${INET_HOME}" -DINET_IMPORT ${INCLUDES[@]} -I$OMNETPP_HOME/include -I$RTI_HOME/include/hla13 -I'$(INET4_PROJ)/src' \
	-L'$(INET4_PROJ)/src' -l'INET' -L$RTI_HOME/lib/gcc4 -lRTI-NG_64 -lFedTime_64 -L/usr/lib/jvm/java-8-openjdk-amd64/jre/lib/amd64/server -lboost_regex -lboost_program_options

make


