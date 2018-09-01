/*
 * nmeaParser.h
 *
 *  Created on: Aug 20, 2018
 *      Author: uli
 */

#ifndef NMEAPARSER_H_
#define NMEAPARSER_H_

/* error codes */
#define nmeaStatus int8_t
#define NMEA_OK 0
#define NMEA_INVALID_HDR      -1
#define NMEA_INVALID_SYNTAX   -2
#define NMEA_BAD_CHECKSUM     -3
#define NMEA_NOMEM            -4

enum nmeaHdr {
	GPRMC,GPGGA, GPVTG,GPGSA,GPGSV,GPGLL,INVALID
};

#define NMEA_SENTENCE_MAX_LEN 80

typedef struct {
	uint8_t hour;
	uint8_t min;
	uint8_t sec;
}nmeaTimeType;

typedef struct {
	uint8_t day;
	uint8_t month;
	uint8_t year;
}nmeaDateType;

typedef struct {
	nmeaTimeType time;
	uint8_t status;           // A = active V=Void
	double latitude;
	uint8_t northOrSouth;
	double longitude;
	uint8_t eastOrWest;
	double speedOverGround;
	double trackAngle;
	nmeaDateType date;
	double magneticVariation;
	uint8_t invalid;
} nmeaRMCType;

typedef struct {
	double trueTrack;
	uint8_t trueTrackChar;
	double magneticTrack;
	uint8_t magneticTrackChar;
	double speedKnots;
	uint8_t speedKnotsChar;
	double speedKmh;
	uint8_t speedKmhChar;
	uint8_t invalid;
} nmeaVTGType;

typedef struct {
	nmeaTimeType time;
	double latitude;
	uint8_t northOrSouth;
	double longitude;
	uint8_t eastOrWest;
	uint8_t fixQuality;
	uint8_t noOfSatellites;
	double horDilution;
	double altitude;
	uint8_t altitudeUnit;
	double heightOfGeoide;
	uint8_t heightOfGeoideUnit;
	uint8_t invalid;
} nmeaGGAType;

typedef struct{
	uint8_t manualAuto;
	uint8_t threeDFix;
	uint8_t prns[12];
	double pdop;
	double horDilution;
	double verDilution;
	uint8_t invalid;
}nmeaGSAType;

typedef struct {
	double latitude;
	uint8_t northOrSouth;
	double longitude;
	uint8_t eastOrWest;
	nmeaTimeType time;
	uint8_t status;           // A = active V=Void
	uint8_t invalid;
} nmeaGLLType;

typedef struct{
	uint8_t prn;
	uint8_t elevation;
	uint16_t azimuth;
	uint8_t snr;
} satelliteSpecs;

typedef struct {
	uint8_t noOfSentences;
	uint8_t sequenceNo;
	uint8_t satellitesInView;
	satelliteSpecs specs[4];
	uint8_t invalid;
} nmeaGSVType;

void nmeaParse(uint8_t *buff,int charCnt);

#endif /* NMEAPARSER_H_ */
