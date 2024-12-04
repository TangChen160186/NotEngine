workspace "NotEngine"
	configurations { "Debug", "Release" }
	platforms { "x64" }
	startproject "OvEditor"

outputdir = "%{wks.location}/../../Bin/"
objoutdir = "%{wks.location}/../../Bin-Int/"
dependdir = "%{wks.location}/../../Dependencies/"
builddir = "%{wks.location}/../../Build/"
-- resdir = "%{wks.location}/../../Resources/"

include "NotEngine"
include "TestBed"