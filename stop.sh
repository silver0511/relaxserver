#!/usr/bin/env bash
kill -9 `ps aux | grep '\<server.1.1.100/>' | grep -v grep | awk {'print $2'}`