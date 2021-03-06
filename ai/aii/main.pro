/*****************************************************************************

                         

******************************************************************************/

implement main
    open core

constants
    className = "main".
    classVersion = "".

clauses
    classInfo(className, classVersion).

class predicates
    acid:(symbol)nondeterm anyflow.
clauses
    acid("br").
    acid("i").
    
class predicates
    alkali:(symbol)nondeterm anyflow.
clauses
    alkali("nh").
    alkali("turnwhite").

class predicates
    oil:(symbol)nondeterm anyflow.
clauses
    oil("petrol").
    oil("turpentine").

class predicates
    other:(symbol)nondeterm anyflow.
clauses
    other("").
    
 class predicates
    patient_mad:(symbol)nondeterm anyflow.
 clauses
    patient_mad("mad").
    
 class predicates
    patient_conscious:(symbol)nondeterm anyflow.
 clauses
    patient_conscious("conscious").
    
 class predicates
    emergent_method:(symbol, symbol, symbol)nondeterm anyflow.
clauses
    emergent_method(Patient,Drug,"drink"):-patient_conscious(Patient),acid(Drug).
    emergent_method(Patient,Drug,"drink"):-patient_conscious(Patient),alkali(Drug).
    emergent_method(Patient,Drug,"drink"):-patient_conscious(Patient),other(Drug).
    emergent_method(Patient,Drug,"vomit"):-patient_conscious(Patient),other(Drug).
    emergent_method(Patient,Drug,"can't vomit"):-patient_conscious(Patient),acid(Drug).
    emergent_method(Patient,Drug,"can't vomit"):-patient_conscious(Patient),alkali(Drug).
    emergent_method(Patient,Drug,"can't vomit"):-patient_conscious(Patient),oil(Drug).
    emergent_method(Patient,Drug,"can't drink"):-patient_mad(Patient),acid(Drug).
    emergent_method(Patient,Drug,"can't vomit"):-patient_mad(Patient),acid(Drug).

clauses
    run():-
        console::init(),
        emergent_method("conscious","br",What),
        stdIO::write("What=",What),
        stdIO::write("\n"),fail.
     run():-
        stdIO::write("\n").    
end implement main

goal
    mainExe::run(main::run).
