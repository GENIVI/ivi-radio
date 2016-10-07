/*! \mainpage IVI Radio Proof of Concept
 * \section intro_sec Introduction
 *
 * Copyright (C) 2013, BMW AG 
 * This file is part of the GENIVI Project IVI Radio PoC
 *
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with ths file, you can obtain one at http://mozilla.org/MPL/2.0 .
 * 
 * \section install_sec Author
 *
 * 	Bernhard Singer   (Bernhard.Singer@partner.bmw.de) 
 * 	Matthias Freundel (Matthias.Freundel@partner.bmw.de) 
 * 	Guido    Ostkamp  (Guido.Ostkamp@partner.bmw.de)
 * 
 * \image html GENIVI_Logo.jpg
 *
 * \section More Information
 * 	can be found here https://collab.genivi.org/wiki/display/genivi/MGEGTunerProofofConcept
 *
 * \section Usage
 * To use the PoC Version 1.0 and execute the possible testcases of Version 1.0 use the testplan
 * https://collab.genivi.org/wiki/download/attachments/27820275/Testplan_1_0.pdf?version=1&modificationDate=1371652128000
 * \n
 * To use the PoC Version 2.0 and execute the possible testcases of Version 2.0 use the testplan
 *
 * \section sec_goals Goals
 * 
 * \subsection ssec_StandardizingInterfaces Standardizing interfaces
 * Standardizing interfaces has the advantage that tuner hardware can be exchanged without  saving to adapt software to the specific commands of this hardware. This means on  
 * the one hand that it is possible to swap hardware manufacturers without big investments of time and effort since the interface stays the same. On the other hand interfaces  
 * also guarantee stability over time, with updated versions of hardware still using the same interface. This point also emphasizes the importance of the right choice of
 * interface functions in order to support future developments. A big role in the standardization of interfaces is played by design patterns. Design patterns are well tested
 * solutions for software architecture. One of the paradigms of design patterns is the separation of logic and presentation which allows the introduction of interfaces. This
 * will be discussed later in more detail.
 *
 * \subsection ssec_embeddedPC Embedded PC
 * Using specialized, purpose-built hardware requires a big amount of development effort and financial investment. In particular the fast developing IT sector poses a big
 * challenge to the automotive industry. In order to lower cost it is feasible to use of-the-shelve hardware which supports the latest technologies like Ethernet.
 *
 *
 * \subsection ssec_EffectiveIPC Effective inter process communication
 * In the past inter process communication was done by the MOST. With the most being a purpose-built communication system only a fixed set of functions is available. Moving to
 * modern platforms like Linux, use a completely open and flexible inter process communication like DBus. Communication with DBus is in no way restricted to any number of
 * messages which is a clear advantage over the MOST. Hence, changes to the features of the tuner system do not require a change in the inter process communication system.
 *
 * \subsection ssec_StandardCombination Combination of broadcast standards
 * The number of different broadcast standards available to the customer is fairly large. Examples are AM, FM, DAB, DMB, DVB-T and SDARS. In order to hides the technical details
 * from the customer a clever combination of broadcast standards makes it easier to use broadcast devices.
 *
 * \section secConcepts Main Concepts
 * \subsection ssec_MVCPattern Separation of logic and view
 * The separation of logic and view also known as Model-View-Controller pattern (MVC) is a software architecture model that separates the representation of information (model)
 * from the user interaction (view). The model itself consists of the application data and business logic. The view in contrast is only a representation of the data. It is
 * possible that many views represent the same model. To handle many views and to suppose user input a Controller is required. The controller converts the user input and 
 * commands the model and the view. The advantage is that the model does not need to know anything about the structure of the view or the controller. So if the view or the
 * controller changes, the model stays untouched. The view only knows the structure of the model, but not the structure of the controller. Because of this it is easily to
 * realize different views without changing the model. Also the model can be presented in different ways and the different views are kept synchronous. The difficulty could be
 * the high complexity by many views. 
 *
 * \subsection ssec_ObserverPattern Observer pattern
 *The communication between the view and the model can be handled in different ways. So it is possible that the view always asks the model, if something in the data has changed.
 *This way of communication would generate lots of communication traffic. A better process would be that the model knows that the view is interested in changes of the model
 * content and the model notifies autonomous. This kind of communication could be realized with the Observer pattern. In this pattern an object (subject) maintains a list of
 * observer. If the objects content changes, the object calls a defined method of the observers and each observer decides to get the new status or not. 
 *
 * \subsection ssec_IOModel Inbox/Outbox Model
 * In the context of data handling the middleware is divided in two parts. One part defines how streams are spitted up, parsed in separate parts and after that saved in storage.
 * This other part is how data from storage is prepared and sent to the view. The first part is call Inbox-Model, the second part Outbox- Model. The Inbox model is very much
 * broadcast standard specific and the Outbox model combines the data access. 
 *
 * \subsection ssec_IModel Inbox Model
 * The data which is transferred via THAL output streams can be divided into three categories: live-streams, live-data and on-demand-data. Live-streams and live- data are time 
 * critical information which have to be sent very fast and directly to further processing and should be stored somewhere in the platform. On-demand- data are information which
 * are stored in the platform and only provided when requested. Depending on the output stream it is necessary for the further proceeding to split up the streams. In usual case
 * the live data, like audio- or video- streams, is directly routed to the sinks after splitting. In some special cases the multimedia streams could itself transfer data. In 
 * this case the stream has to be parsed first, before sending it to the sink. The live data streams have to be decoded by components outside the tuner middleware. After
 * splitting the output streams in the Stream Manager, the data streams are sent to the Parser. The Parser has the function to decode the data streams. The decoded data is
 * categorized in two groups: live-data (subtitle) and on-demand- data (names, PI). In the DAH the data is prepared for storing. The live-data is sent directly to a pipe which
 * can be handled dynamically. For the on-demand data the storing location must be chosen. It is possible to save the data in conveniently way in a data base or a file system. 
 * If data has to be filtered it could be saved it in the data base. While big data could be stored in a file system. XML will be the preferredis one of the possible formats to
 * store the data. For this way of saving data for example all the browser data is intended. Using XML supports the idea separation of hardly distinguishing between logic and
 * data. Furthermore XML allows an independent presentation by can be translated using style sheets.
 *
 *
 * \subsection ssec_OModel Outbox
 * After saving data in a database or file system, it could be requested. These requests are handled in the station or browser manager and relayed to the DAH. This manager reads
 * the data from the storages and transfers it back. Both managers (station and browser) can now convert the data in any format and transfer it via the DBus to the requestor.
 *
 * \subsection ssec_StandardCombination Combination of all broadcast standards
 * The goal for the concept of combination of all broadcast standards is that the clients, using the Tuner API, haven`t to decide from which sources (FM, DAB...) the content
 * (e.g. audio, video, data content...) is requested. This selection is done in the middleware depending on the current capacity and reception quality. The central object for
 * the interface user is the station. The station abstracts channels and its components. It stands for all channels over all standards with the same content. Content is
 * called <u>component</u>, these components could be audio, video or other data content, like EPG. Every station is connected with a list of components. At last a component is
 * broadcasted by channels. It could be the same over many standards like the audio signal or unique for standard specific content (e.g. DAB with Journaline). This combining and
 * adding content to one station allows to hide the  beneath lying channels. 
 *
 */



