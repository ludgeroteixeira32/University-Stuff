FROM debian:stable
LABEL maintainer="spa@debian.org"

# -- public ports -------------------------------------------------------------

## EXPOSE 80/tcp

# -- environment variables ----------------------------------------------------

ENV WORKDIR=/root

WORKDIR ${WORKDIR}

ENV PATH=$PATH

# -- go -----------------------------------------------------------------------

RUN apt update
RUN apt install -y --no-install-recommends \
    	    gcc \
	    m4 \
	    bison \
	    flex \
	    wget
RUN wget http://www.di.uevora.pt/~spa/sim2c.deb
RUN dpkg -i sim2c.deb

CMD bash
CMD sim2c
