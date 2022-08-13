package main

import (
	"net/http"
	"time"
)

type (
	handler struct{}
)

const (
	readTimeout       = 10 * time.Second
	readHeaderTimeout = 5 * time.Second
	writeTimeout      = 10 * time.Second
	idleTimeout       = readTimeout
	maxHeaderBytes    = http.DefaultMaxHeaderBytes
)

func (*handler) ServeHTTP(w http.ResponseWriter, _ *http.Request) {
	if _, err := w.Write([]byte("woot\n")); err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
	}
}

func main() {
	server := &http.Server{
		Addr:              ":8080",
		Handler:           &handler{},
		TLSConfig:         nil,
		ReadTimeout:       readTimeout,
		ReadHeaderTimeout: readHeaderTimeout,
		WriteTimeout:      writeTimeout,
		IdleTimeout:       idleTimeout,
		MaxHeaderBytes:    maxHeaderBytes,
		TLSNextProto:      nil,
		ConnState:         nil,
		ErrorLog:          nil,
		BaseContext:       nil,
		ConnContext:       nil,
	}

	if err := server.ListenAndServe(); err != nil {
		panic(err)
	}
}
