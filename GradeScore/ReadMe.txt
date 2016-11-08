================================================================================
    MICROSOFT FOUNDATION CLASS-BIBLIOTHEK: GradeScore-Projektübersicht
===============================================================================

Diese GradeScore-Anwendung wurde vom Anwendungs-Assistenten für Sie erstellt. Diese Anwendung zeigt nicht nur die Grundlagen der Verwendung von Microsoft Foundation Classes, sondern dient auch als Ausgangspunkt für das Schreiben Ihrer Anwendung.

Diese Datei bietet eine Übersicht über den Inhalt der einzelnen Dateien, aus
denen Ihre GradeScore-Anwendung besteht.

GradeScore.vcxproj
    Dies ist die Hauptprojektdatei für VC++-Projekte, die mit dem Anwendungs-Assistenten generiert werden. Sie enthält Informationen über die Version von Visual C++, mit der die Datei generiert wurde, sowie über die Plattformen, Konfigurationen und Projektfunktionen, die im Anwendungs-Assistenten ausgewählt wurden.

GradeScore.vcxproj.filters
    Dies ist die Filterdatei für VC++-Projekte, die mithilfe eines Anwendungs-Assistenten erstellt werden. Sie enthält Informationen über die Zuordnung zwischen den Dateien im Projekt und den Filtern. Diese Zuordnung wird in der IDE zur Darstellung der Gruppierung von Dateien mit ähnlichen Erweiterungen unter einem bestimmten Knoten verwendet (z. B. sind CPP-Dateien dem Filter "Quelldateien" zugeordnet).

GradeScore.h
    Dies ist die Hauptheaderdatei für die Anwendung.
    Sie enthält andere projektspezifische Header (einschließlich Resource.h) und deklariert die CGradeScoreApp-Anwendungsklasse.

GradeScore.cpp
    Dies ist die wichtigste Anwendungsquelldatei, die die Anwendungsklasse CGradeScoreApp enthält.

GradeScore.rc
    Dies ist eine Auflistung aller vom Programm verwendeten Microsoft Windows-Ressourcen. Sie enthält die Symbole, Bitmaps und Cursor, die im Unterverzeichnis "RES" gespeichert werden. Diese Datei kann direkt in Microsoft Visual C++ bearbeitet werden. Ihre Projektressourcen befinden sich in 1031.

res\GradeScore.ico
    Dies ist eine Symboldatei, die als Anwendungssymbol verwendet wird. Dieses Symbol ist in der Hauptressourcendatei GradeScore.rc enthalten.

res\GradeScore.rc2
    Diese Datei enthält Ressourcen, die nicht von Microsoft Visual C++ bearbeitet werden. Sie sollten alle Ressourcen, die nicht mit dem Ressourcen-Editor bearbeitet werden können, in dieser Datei platzieren.

/////////////////////////////////////////////////////////////////////////////

Für das Hauptrahmenfenster:
    Das Projekt enthält eine Standard-MFC-Schnittstelle.

MainFrm.h, MainFrm.cpp
    Diese Dateien enthalten die CMainFrame-Rahmenklasse, die abgeleitet ist von
    CFrameWnd und alle SDI-Rahmenfunktionen steuert.

res\Toolbar.bmp
    Diese Bitmapdatei wird zum Erstellen von Kachelbildern für die Symbolleiste verwendet.
    Die ursprüngliche Symbol- und Statusleiste werden in der CMainFrame-Klasse erstellt. Bearbeiten Sie diese Bitmapdatei für die Symbolleiste mit dem Ressourcen-Editor, und aktualisieren Sie das IDR_MAINFRAME TOOLBAR-Array in GradeScore.rc, um Symbolleistenschaltflächen hinzuzufügen.
/////////////////////////////////////////////////////////////////////////////

Der Anwendungs-Assistent erstellt einen Dokumententyp und eine Ansicht:

GradeScoreDoc.h, GradeScoreDoc.cpp - das Dokument
    Diese Dateien enthalten Ihre CGradeScoreDoc-Klasse. Bearbeiten Sie diese Dateien, um Ihre speziellen Dokumentdaten hinzuzufügen sowie um das Speichern und Laden von Dateien zu implementieren (über CGradeScoreDoc::Serialize).

GradeScoreView.h, GradeScoreView.cpp - die Ansicht des Dokuments
    Diese Dateien enthalten Ihre CGradeScoreView-Klasse.
    CGradeScoreView-Objekte werden verwendet, um CGradeScoreDoc-Objekte anzuzeigen.




/////////////////////////////////////////////////////////////////////////////

Andere Funktionen:

ActiveX-Steuerelemente
    Die Anwendung bietet Unterstützung für ActiveX-Steuerelemente.

Datenbankunterstützung
    Der Anwendungs-Assistent hat grundlegende Datenbankunterstützung für das Programm hinzugefügt. Es sind nur die benötigten Dateien enthalten.

/////////////////////////////////////////////////////////////////////////////

Andere Standarddateien:

StdAfx.h, StdAfx.cpp
    Mit diesen Dateien werden eine vorkompilierte Headerdatei (PCH) mit dem Namen GradeScore.pch und eine vorkompilierte Typendatei mit dem Namen StdAfx.obj erstellt.

Resource.h
    Dies ist die Standardheaderdatei, die neue Ressourcen-IDs definiert. Die Datei wird mit Microsoft Visual C++ gelesen und aktualisiert.

GradeScore.manifest
	Anwendungsmanifestdateien werden von Windows XP verwendet, um die Abhängigkeit einer Anwendung von bestimmten Versionen paralleler Assemblys zu beschreiben. Das Ladeprogramm verwendet diese Informationen, um die entsprechende Assembly aus dem Assemblycache oder privat von der Anwendung zu laden. Das Anwendungsmanifest kann zur Neuverteilung als externe .manifest-Datei einbezogen werden, die im selben Ordner wie die ausführbare Datei der Anwendung installiert ist, oder sie wird der ausführbaren Datei in Form einer Ressource hinzugefügt.
/////////////////////////////////////////////////////////////////////////////

Weitere Hinweise:

Der Anwendungs-Assistent weist Sie mit "TODO:"-Kommentaren auf Teile des Quellcodes hin, die Sie ergänzen oder anpassen sollten.

Wenn Ihre Anwendung MFC in einer gemeinsam genutzten DLL verwendet, müssen die MFC-DLLs mitverteilt werden. Wenn Ihre Anwendung eine andere Sprache als Systemsprache verwendet, müssen auch die entsprechende mfc110XXX.DLL für die lokalisierten Ressourcen mitverteilt werden.
Weitere Informationen zu diesen beiden Themen finden Sie im Abschnitt zur Neuverteilung von Visual C++-Anwendungen in der MSDN-Dokumentation.

/////////////////////////////////////////////////////////////////////////////
