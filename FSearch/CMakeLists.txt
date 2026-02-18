cmake_minimum_required(VERSION 3.10)

# Nome del progetto e lingua
project(fsearch C)

# Trova libcurl
find_package(CURL REQUIRED)

# Specifica dove cercare gli header
include_directories(include)

# Lista dei file sorgente
set(SOURCES
    src/main.c
    src/utils.c
    src/cJSON.c
    src/setupCurlCjson.c
)

# Crea l'eseguibile
add_executable(fsearch ${SOURCES})

# Aggiungi path include di curl
target_include_directories(fsearch PRIVATE ${CURL_INCLUDE_DIRS})

# Linka la libreria curl
target_link_libraries(fsearch PRIVATE ${CURL_LIBRARIES})


# -------------------------------
# Installazione globale
# -------------------------------
# RUNTIME DESTINATION = dove finisce l'eseguibile
# Qui "bin" è relativo al prefix
install(TARGETS fsearch
    RUNTIME DESTINATION bin
)
