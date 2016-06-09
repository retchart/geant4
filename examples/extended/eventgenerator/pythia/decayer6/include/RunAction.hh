//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: RunAction.hh,v 1.1 2008/11/03 11:48:35 gcosmo Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
// ----------------------------------------------------------------------------

#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

// ----------------------------------------------------------------------------

class G4Run;

class RunAction : public G4UserRunAction
{
  public:

    RunAction();
   ~RunAction();

    void BeginOfRunAction(const G4Run*);
    void   EndOfRunAction(const G4Run*);
    
    void fillPerEvent(G4double, G4double, G4double, G4double); 

  private:

    G4double sumEAbs, sum2EAbs;
    G4double sumEGap, sum2EGap;

    G4double sumLAbs, sum2LAbs;
    G4double sumLGap, sum2LGap;    
};

// ----------------------------------------------------------------------------

#endif