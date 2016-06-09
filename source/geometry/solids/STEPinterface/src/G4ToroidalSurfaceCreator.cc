//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// $Id: G4ToroidalSurfaceCreator.cc,v 1.5 2002/11/21 16:49:50 gcosmo Exp $
// GEANT4 tag $Name: geant4-05-00 $
//
// 
// ----------------------------------------------------------------------
// Class G4ToroidalSurfaceCreator
//
// Authors: J.Sulkimo, P.Urban.
// Revisions by: L.Broglia, G.Cosmo.
//
// History:
//   18-Nov-1999: First step of re-engineering - G.Cosmo
// ----------------------------------------------------------------------

#include "G4ToroidalSurfaceCreator.hh"
#include "G4GeometryTable.hh"
#include "G4ToroidalSurface.hh"

G4ToroidalSurfaceCreator G4ToroidalSurfaceCreator::csc;

G4ToroidalSurfaceCreator::G4ToroidalSurfaceCreator()
{
  G4GeometryTable::RegisterObject(this);
}

G4ToroidalSurfaceCreator::~G4ToroidalSurfaceCreator() {}

G4ToroidalSurfaceCreator G4ToroidalSurfaceCreator::GetInstance()
{
  return csc;
}

void G4ToroidalSurfaceCreator::CreateG4Geometry(STEPentity& Ent)
{
  G4Axis2Placement3D* place;
  G4double majorRadius, minorRadius;

  // Get the placement
  G4String attrName("position");
  STEPattribute *Attr = GetNamedAttribute(attrName, Ent);
  STEPentity* TmpEnt= *Attr->ptr.c;
  void *tmp =G4GeometryTable::CreateObject(*TmpEnt);
  place = (G4Axis2Placement3D*)tmp;
  
  // get radii
  attrName = "major_radius";
  Attr = GetNamedAttribute(attrName, Ent);
  majorRadius = *Attr->ptr.r;
  attrName = "minor_radius";
  Attr = GetNamedAttribute(attrName, Ent);  
  minorRadius = *Attr->ptr.r;

  
  G4ToroidalSurface* aTorus = 0;
  if (place)
    aTorus = new G4ToroidalSurface( (*place).GetLocation() ,
				    (*place).GetPZ()       ,
				    (*place).GetPX()       ,
				    minorRadius            ,
				    majorRadius            );
  else
    G4cerr << "WARNING - G4ToroidalSurfaceCreator::CreateG4Geometry" << G4endl
           << "\tUnexpected NULL axis placement (G4Axis2Placement3D) !" << G4endl
	   << "\tToroidal Surface NOT created." << G4endl;

  createdObject = aTorus;

}

void G4ToroidalSurfaceCreator::CreateSTEPGeometry(void* G4obj)
{
  G4ToroidalSurface* tor = (G4ToroidalSurface*)G4obj;
  SdaiToroidal_surface* srf= new SdaiToroidal_surface();
  // Get placement
  G4String placementName("Axis2Placement3d");
  void * tmp =G4GeometryTable::CreateSTEPObject(&tor, placementName);
  SdaiAxis2_placement_3d *place = (SdaiAxis2_placement_3d*)tmp;
  srf->position_(place);
  // radiis
  srf->minor_radius_(tor->GetMinRadius());
  srf->major_radius_(tor->GetMaxRadius());  

  // Set STEP info
  srf->SetFileId(GetNextId());
  srf->name_("");
  
  // Write out object 
  srf->STEPwrite(G4cout);

  createdObject = srf;
}