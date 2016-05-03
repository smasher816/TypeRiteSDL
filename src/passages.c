#include "passages.h"
#include <stdlib.h>
#define ARRAYLEN(x) (sizeof(x) / sizeof(x[0]))

/*
A  Accountant
C  Carpenter
D  Dietitian
E  Engineer
G  Geologist
H  Hotel Manager
I  Interior Designer
J  Jeweler
L  Lawyer
M  Mechanic
N  Newscaster
O  Officer
P  Paramedic
S  Systems Analyst
T  Technologist
W  Waiter or Waitress
*/

char* text_A[] = {
	"The best accountants work as well with people as they do with systems and",
	"computers.  They are patient.  They are able to concentrate for hours at",
	"their desks.  They must be able to perform accurate, precise work with",
	"numbers as they maintain financial records.",

	"Accountants sometimes design or modify accounting systems, audit",
	"contracts, or prepare periodic financial statements and other",
	"management reports.  It is most important that they do honest, accurate",
	"work with limited supervision.",

	"Initial experience in this field can be gained as a bookkeeper or as an",
	"accounting clerk.  Many employers require accountants to pass an exam to",
	"become certified.  Some employers may require accredited status.  That is",
	"also achieved by passing an exam, but it requires continuing education",
	"to earn renewal every two years.  Naturally, accountants with higher",
	"degrees and certificates earn more money.  Also, larger firms generally",
	"pay higher starting salaries.  College graduates will continue to be in",
	"greater demand for accounting jobs.  Many employers prefer to hire",
	"college graduates who have worked several hours a week in a business or",
	"accounting firm while they were in school.  Jobs for those without a",
	"college degree will occur mainly in small companies and small",
	"accounting firms.  A growing number of large employers prefer",
	"accountants who are familiar with computers.",

	"Almost one million Americans are employed as accountants today.  More",
	"will be needed as the use of computers increases.  More will also be",
	"needed because of the increasing pressure on businesses and government",
	"agencies to improve budgeting and accounting procedures."
};
char* text_C[] = {
	"Carpenters make up the largest group of building trade workers.  Because",
	"their skills are so important and varied, they can be found everywhere",
	"in the country.  Other building trade workers often are able to find",
	"work only in limited geographic areas.",

	"Carpenters who are not doing construction work may do maintenance work.",
	"For example, school districts employ carpenters to repair desks,",
	"cabinets and doors.  They also replace glass and tiles for the schools.",
	"Modern carpenters work with plastic and fiberglass as well as wood.",
	"Factories may employ carpenters to install machinery.",

	"All carpenters use handtools such as hammers, saws, chisels and planes.",
	"They use power tools such as power saws, drills and rivet guns.  They",
	"must be able to measure accurately.  Some jobs require the ability to",
	"read blueprints.",

	"Carpentry is commonly divided into rough carpentry and finish carpentry.",
	"Rough carpentry includes making the frameworks of buildings, scaffolds,",
	"and wooden forms for concrete.  It also includes constructing docks,",
	"bridges or supports for tunnels.  Finish carpentry includes building",
	"stairs and installing doors, cabinets, paneling and molding.  Skilled",
	"carpenters do both rough and finish work.  The best way to become a",
	"carpenter is to work with a master carpenter as an apprentice for four",
	"years.  Most employers prefer beginners with a high school or vocational",
	"school education.  Courses in carpentry, shop, mechanical drawing and",
	"general math are very helpful."
};
char* text_D[] = {
	"Dietitians plan meals and supervise the food service workers who prepare",
	"and serve the meals.  They also manage the purchasing and accounting.",
	"Their goal is to provide balanced meals which are appetizing.",

	"There are four major groups of dietitians.  The largest group is that of",
	"the clinical dietitians.  They plan the diets of patients in hospitals,",
	"nursing homes or clinics.  They work closely with doctors.  They often",
	"give instructions about diets to patients and their families.",

	"Those who work for institutions where meals must be planned on a large",
	"scale are called administrative dietitians.  They may handle food",
	"budgets which amount to millions of dollars every year when they work",
	"in hospitals or universities.",

	"Research dietitians usually work for medical centers or universities.",
	"They do research about such things as how the body uses food.  Two",
	"interesting areas of research are food needs of the aging and food for",
	"space travelers.",

	"The fourth group of dietitians is that of the educators.",

	"The work of nutritionists is similar to that of the four groups of",
	"dietitians.  They often teach and work in community health programs or",
	"they find jobs in the food industry.  Public health nutritionists must",
	"earn a graduate degree.  All dietitians must be college graduates.",
	"They usually major in foods."
};
char* text_E[] = {
	"It was not long ago that our country had too many engineers.  Now two",
	"of the top ten best job opportunities in the next ten years are in the",
	"field of engineering.  It is predicted that there will be more than a",
	"forty percent increase in the number of aerospace engineers.  The",
	"outlook for electrical engineers is almost as good.",

	"Most aerospace engineers work for the aircraft industry.  Some work for",
	"the government.  A few are with consulting firms or at colleges and",
	"universities.",

	"The work of the aerospace engineer is to design, test and help produce",
	"aircraft.  That includes missiles and spacecraft.  It also includes",
	"helicopters.  Some aerospace engineers may work only on structural",
	"design.  Others may deal with navigation.",

	"Some electrical engineers work with generating and distributing",
	"electrical power.  Others may work on electric motors or on the lighting",
	"and wiring of buildings.  This branch of engineering is the largest.",
	"Electronic engineers may work with computers, television sets or",
	"stereos.  The increasing demand for computers is the major cause for",
	"growth in this field."
};
char* text_G[] = {
	"These days a geologist has no trouble finding work.  However, that work",
	"will usually be found in the five states which have the largest mineral",
	"and oil deposits.  The job will probably be in private industry.  There",
	"is a good chance that it will be in the oil industry or natural gas",
	"industry.  It might be for a mining company.  A third of all geologists",
	"work in colleges or universities.",

	"A geologist must be a college graduate.  Advanced degrees are helpful",
	"for promotion to a better job.  Geologists usually begin their careers",
	"as research assistants in labs or in field exploration.  They often",
	"travel to remote areas by jeep or by helicopter.  Once there, they may",
	"cover large areas by foot.  They almost always work in teams.  Those in",
	"minimg teams often work underground.",

	"Geologists study the structure and composition of the earth and its",
	"history.  The three general areas are earth materials, earth processes",
	"and earth history.  Since this includes so much, geologists usually",
	"specialize.  Some geologists choose sites for building roads and",
	"tunnels.  Some study precious gem stones.  Others study the ocean floor.",
	"Still others determine the age of rocks.  It is geologists who are",
	"trying to predict when earthquakes will occur.  Plant and animal fossils",
	"are studied by geologists.  Those who try to find oil and minerals",
	"outnumber all of the others.",

	"Tools geologists use range from chisels and cameras to complex lab",
	"equipment and computers."
};
char* text_H[] = {
	"Salaries of hotel and motel managers vary greatly.  Usually the",
	"amount earned depends on the size of the hotel or motel.  General",
	"managers of large hotels often have several assistants.  One of these",
	"may be in charge of the hotel restaurant.  That person almost always",
	"has had experience in the restaurant field.  Another assistant may",
	"arrange banquets and conventions.  Still another may be in charge of",
	"accounting.",

	"Hotel or motel chains often have central offices.  These offices",
	"purchase supplies and arrange advertising.  Managers who work for",
	"chains may be asked to start a new hotel.  Sometimes a successful",
	"manager is sent to a hotel which is not making a profit.  Chains may",
	"offer better opportunities for advancement because employees can",
	"transfer when an opening occurs.",

	"Experience generally is the biggest factor in getting a good job as",
	"a hotel or motel manager.  A college degree in hotel management is",
	"becoming more important.  Such college programs include courses in",
	"accounting and data processing.  Also included are housekeeping and",
	"food service management.  Sometimes large hotels sponsor training",
	"programs which rotate trainees from one department to another.",

	"Managers must be able to cope with unexpected problems and keep the",
	"guests happy.  Successful managers direct the hotel staff to form a",
	"profitable team."
};
char *text_I[] = {
	"There is a great deal of competition for jobs in interior design.  It",
	"is expected that employment of designers will increase about as fast as",
	"the average for all jobs.  Those with talent and training will have the",
	"best opportunities.  Almost as important as talent is the ability to",
	"work well with people.  A successful designer must be organized and",
	"good at handling details.  The job requires placing orders, figuring",
	"estimates and maintaining records.",

	"Some experienced interior designers run their own firms.  Some work for",
	"large department stores.  Hotel and restaurant chains often have their",
	"own designers, as do some architects.",

	"Formal training in interior design is more important than it used to be.",
	"It takes three years to complete the program at some schools of interior",
	"design.  College and university programs take four years.  The courses",
	"include history of art, freehand drawing and drafting.  Materials such",
	"as woods, plastics, metals and fabrics are studied.",

	"Interior designers do not just decorate rooms to make them look pretty.",
	"They plan efficient use of space.  This includes everything from proper",
	"lighting and ample storage to floor plans which are matched to the uses",
	"the client has in mind for each room.  The best interior designers are",
	"able to make an interior suit the personality of the client."
};
char *text_J[] = {
	"Many people think of a jeweler as a salesperson.  The job is usually",
	"far more than that.  Highly skilled jewelers still make jewelry by hand.",
	"They design and shape metal with pliers or cast it in molds.  Sometimes",
	"parts are soldered together to make a finished piece.  Chemicals and",
	"polishing compounds may be used in the final steps.  Most jewelry is",
	"mass produced today.  Each craftsman on the assembly line does only",
	"one part of the job.",

	"Most jewelers who are employed in producing precious jewelry work in",
	"or near New York.  There are also more jewelry stores and repair shops",
	"in big cities than in small towns.  Jobs in the field are to be found",
	"in urban areas.",

	"Most jewelers learn their skills on the job.  Some technical schools",
	"offer instruction in jewelry repair and jewelry making.  The courses",
	"may take from six months to three years.  The training program in the",
	"precious jewelry industry takes three to four years.",

	"Jobs which are closely related to that of the jeweler are those of gem",
	"cutters and gemologists.  Some jewelers do watch repair or hand",
	"engraving.  Some are silversmiths."
};
char *text_L[] = {
	"To practice law in the courts of any state, a person must be admitted",
	"to its bar.  That is usually done by passing the bar examination.",
	"A few states allow graduates of their own law schools to practice",
	"without passing an exam.",

	"Most students attend college for four years and then law school for",
	"three years before attempting the bar exam.  It is often necessary to",
	"pass a difficult test just to enter law school.  For every person who",
	"is accepted by a law school, another is not admitted because there",
	"simply is not room.",

	"Even after the bachelor of law degree is earned, most lawyers start as",
	"law clerks.  They do research for experienced lawyers or judges.  They",
	"receive a salary.  After several years on a salary, many lawyers go",
	"into practice for themselves.  Later still, some may become judges.",

	"An increasing number of law school graduates will enter fields where",
	"legal training is not required, but is an asset.  Banks and insurance",
	"firms will seek them as managers.  They will find business positions",
	"with real estate companies.  Many agencies of the government will need",
	"them as administrators.",

	"As the law and society grow more complex, the lawyer tends to limit the",
	"scope of his work.  That means more study and research for the lawyer."
};
char *text_M[] = {
	"Auto mechanics repair and service cars, trucks and even heavy",
	"construction equipment.  One of the most valuable skills mechanics",
	"need is the ability to make a quick and accurate diagnosis when a car",
	"is not working properly.  Although most auto mechanics perform a",

	"variety of repairs, others specialize.  Brake mechanics adjust brake",
	"linings, repair hydraulic cylinders, and make other repairs of brake",
	"systems.  Automatic transmission specialists work on gear trains,",
	"couplings, hydraulic pumps and other parts of automatic transmissions.",
	"Such repairs require considerable experience and training, including a",
	"knowledge of hydraulics.",

	"Courses in automobile repair are offered in many high schools,",
	"vocational schools and private trade schools.  An apprenticeship",
	"program which takes three to four years is recommended.  Such programs",
	"are offered through many auto dealers and independent repair shops.",
	"Apprenticeship programs include both classroom instruction and practical",
	"experience.",

	"Most mechanics learn the trade on the job.  Beginners usually start as",
	"helpers, lubrication workers, or gas station attendants.  They acquire",
	"skills gradually by working with skilled mechanics.  A beginner can make",
	"simple repairs after a few months.",

	"Beginners are paid an hourly rate.  Skilled auto mechanics in repair",
	"shops often receive a percentage of the labor charges for repairs they",
	"make.  They may be required to buy their own tools.  Such tools may",
	"cost more than a thousand dollars.  Mechanics can expect steady work.",
	"Economic conditions have little effect on the auto repair business."
};
char *text_N[] = {
	"A newswriter selects news and writes what is called copy.  This copy",
	"is then read on the air by a newscaster.  Sometimes the newscaster is",
	"simply an announcer.  The job of the announcer often includes",
	"introducing programs, guests and musical selections.  Radio announcers",
	"deliver most of the live commercial messages.  In small stations they",
	"operate the control board and even sell time.  They may be called upon",
	"to write both commercial and news copy.",

	"The real news reporters actually gather information about newsworthy",
	"events.  They analyze the information as they write their own copy.",
	"They often report special news events from the scene.  News reporters",
	"may choose to work in a special field.  Such a field might be health",
	"or sports.  Those who choose foreign affairs may be sent abroad by",
	"their networks.",

	"It is the news directors who plan and supervise all news and special",
	"events coverage.  Associate directors work out detailed plans and",
	"schedules.  They may arrange for artwork and film slides.  They may",
	"assist in timing.",

	"A high school diploma is enough for an entry level job in broadcasting.",
	"Courses in speech and drama are helpful to persons seeking careers as",
	"announcers.  Most beginners start at low salaries.  Stations in big",
	"cities seek only people with experience.  It is predicted that there",
	"will be more and more openings in this growing industry, but these",
	"openings will also attract large numbers of jobseekers."
};
char *text_O[] = {
	"Besides their usual duties, police officers must be able to give first",
	"aid to accident victims.  A few work on accident prevention programs.",
	"Some operate communications systems or computers.  A few may be part",
	"of mobile rescue teams.  Those who are detectives rarely wear uniforms.",

	"Civilians often assist with police paper work and investigation.  Some",
	"may be chemists in crime labs.  Others may be secretaries or may work",
	"in fields such as firearms, fingerprints or computers.",

	"Some police work is done in special places.  An officer may work with",
	"a harbor patrol unit or in a helicopter.  A fish and game warden",
	"enforces game laws while also making surveys of wildlife resources by",
	"collecting data about plants and animals.",

	"All police officers receive classroom instruction in the laws they are",
	"to enforce.  All must learn the procedures to follow when enforcing",
	"laws.  Some take advanced courses in police science, law enforcement",
	"or criminology.  Federal agents usually have law degrees or have",
	"majors in accounting.  Then they must spend fifteen weeks at a special",
	"academy.",

	"A college education is not required to be a police officer.  Larger",
	"cities usually do require a high school education.  Almost all police",
	"departments have standards for physical size and strength.  Candidates",
	"must be agile.  The police conduct interviews and background checks to",
	"be sure they appoint officers who have good character traits."
};
char *text_P[] = {
	"The hardest part of the job of a paramedic is working as fast as",
	"possible without making mistakes.  Paramedics must be emotionally",
	"stable.  They usually work in teams of two.  They may be employed by a",
	"hospital, a police or fire department or a private firm.  Since",
	"paramedics are needed at all hours, they are often asked to work nights",
	"and weekends.",

	"The duties of paramedics are varied.  They must be good drivers.  They",
	"must know the best and fastest routes in the area where they work.",
	"Time cannot be wasted hunting for an address.  At the scene of an",
	"emergency they often have to care for victims of accidents or persons",
	"who are ill.  They might be called upon to assist in childbirth or to",
	"calm a mentally disturbed patient.  Giving first aid to poison or burn",
	"victims takes added skill.  An ambulance driver may never give a",
	"patient medicine.  Working by way of radio with doctors, paramedics may",
	"administer drugs.  Radio contact also helps the hospital to be ready",
	"for each case.",

	"Over half of the ambulance attendants in this country are unpaid",
	"volunteers.  The job is exciting and attractive to many.  On the other",
	"hand, many openings for paramedics are created by those who find it too",
	"demanding.  They leave because of the physical and mental stress.  It",
	"is not an easy job.  It requires dedication."
};
char *text_S[] = {
	"Computer programmers write detailed instructions for computers.",
	"They list the steps computers must follow to solve a problem.  The",
	"detailed steps must be placed in logical order.  A program is a series",
	"of such coded instructions.  It must be written in a language which",
	"computers can understand.",

	"Simple programs can be written in a few hours.  Complex programs may",
	"require a year of work.  A team of programmers may work together on",
	"programs that use complex mathematics or many data files.",

	"Ingenuity and imagination are important to programmers who must find",
	"new ways to solve problems.  The job calls for patience and",
	"persistence.  Many times programmers are required to work with",
	"accuracy under pressure.  Programming is seldom a nine to five job.",

	"Most computer programmers are college graduates.  Employers using",
	"computers for science or engineering prefer programmers who have taken",
	"college math.  Employers using computers for business prefer",
	"programmers who have taken college courses in data processing,",
	"accounting, and business administration.  Programmers who work either",
	"in business, science or engineering are called applications programmers.",
	"Programmers who are in charge of entire computer systems are called",
	"systems programmers.  They usually work for large organizations."
};
char *text_T[] = {
	"There are three levels of medical lab workers.  At the top are the",
	"technologists.  They have at least four years of education beyond high",
	"school.  They perform complicated tests on body fluids or tissue",
	"samples.  They may use microscopes to detect the presence of diseases.",
	"They may make cultures to check for bacteria or parasites.  They may",
	"type and cross match blood samples.  Most medical technologists conduct",
	"tests related to the examination and treatment of patients.  They work",
	"under doctors.  Others do research under chemists.  A few teach.  Some",
	"are administrators.",

	"Medical lab technicians generally have two years of college training.",
	"They also perform a wide range of tests that require a high level of",
	"skill.  The technician does not have to have the depth of knowledge",
	"demanded of the technologist.",

	"Lab assistants generally have one year of training.  In large labs",
	"they may specialize in one area of work.  For example, they may",
	"identify abnormal blood cells on slides.  They usually perform routine",
	"tests.  Assistants clean and store equipment and they keep records.",

	"The use of automated lab test equipment will lead to a decreased need",
	"for skilled technologists.  At the same time, it will lead to an",
	"increased need for technicians and assistants to run the equipment."
};
char *text_W[] = {
	"Over one million people are employed as waiters or waitresses in",
	"this country.  Most work in restaurants, but some work in hotels,",
	"colleges and factories.  Jobs are most plentiful in large cities",
	"and tourist areas.  Vacation resorts offer seasonal employment.",
	"Because of that, some waiters and waitresses move back and forth",
	"between summer and winter resort areas.",

	"More than half of the waiters and waitresses work less than forty",
	"hours a week.  One out of four is a high school or college student who",
	"works in this field while he or she attends school.",

	"Job openings are expected to be plentiful in the coming years.",
	"Beginners will find their chances of getting a job in an informal",
	"restaurant are better than in an expensive restaurant.  The competition",
	"is keen at elegant restaurants where earnings are higher because tips",
	"are larger and surroundings are more pleasant.  Most employers prefer",
	"to hire someone with at least two or three years of high school.",

	"Sometimes it is necessary to start as a busboy or dining room attendant.",
	"A first job is often that of a food counter worker.  In very small",
	"restaurants, there is no opportunity for advancement.  Larger places",
	"offer the possibility of becoming a hostess or host or of being",
	"a supervisor or manager."
};

Passage passage_A = {'A', "Accountant",			&text_A, ARRAYLEN(text_A)};
//Passage passage_B = {'B', "		",			&text_B, ARRAYLEN(text_B)};
Passage passage_C = {'C', "Carpenter",			&text_C, ARRAYLEN(text_C)};
Passage passage_D = {'D', "Dietitian",			&text_D, ARRAYLEN(text_D)};
Passage passage_E = {'E', "Engineer",			&text_E, ARRAYLEN(text_E)};
//Passage passage_F = {'F', "		",			&text_F, ARRAYLEN(text_F)};
Passage passage_G = {'G', "Geologist",			&text_G, ARRAYLEN(text_G)};
Passage passage_H = {'H', "Hotel Manager",		&text_H, ARRAYLEN(text_H)};
Passage passage_I = {'I', "Interior Designer",	&text_I, ARRAYLEN(text_I)};
Passage passage_J = {'J', "Jeweler",			&text_J, ARRAYLEN(text_J)};
//Passage passage_K = {'K', "		",			&text_K, ARRAYLEN(text_K)};
Passage passage_L = {'L', "Lawyer",				&text_L, ARRAYLEN(text_L)};
Passage passage_M = {'M', "Mechanic",			&text_M, ARRAYLEN(text_M)};
Passage passage_N = {'N', "Newcaster",			&text_N, ARRAYLEN(text_N)};
Passage passage_O = {'O', "Officer",			&text_O, ARRAYLEN(text_O)};
Passage passage_P = {'P', "Paramedic",			&text_P, ARRAYLEN(text_P)};
//Passage passage_Q = {'Q', "		",			&text_Q, ARRAYLEN(text_Q)};
//Passage passage_R = {'R', "		",			&text_R, ARRAYLEN(text_R)};
Passage passage_S = {'S', "Systems Analyst",	&text_S, ARRAYLEN(text_S)};
Passage passage_T = {'T', "Technologist",		&text_T, ARRAYLEN(text_T)};
//Passage passage_U = {'U', "		",			&text_U, ARRAYLEN(text_U)};
//Passage passage_V = {'V', "		",			&text_V, ARRAYLEN(text_V)};
Passage passage_W = {'W', "Waiter or Waitress",	&text_W, ARRAYLEN(text_W)};
//Passage passage_X = {'X', "		",			&text_X, ARRAYLEN(text_X)};
//Passage passage_Y = {'Y', "		",			&text_Y, ARRAYLEN(text_Y)};
//Passage passage_Z = {'Z', "		",			&text_Z, ARRAYLEN(text_Z)};

Passage *passages[] = {
&passage_A,
NULL,
&passage_C,
&passage_D,
&passage_E,
NULL,
&passage_G,
&passage_H,
&passage_I,
&passage_J,
NULL,
&passage_L,
&passage_M,
&passage_N,
&passage_O,
&passage_P,
NULL,
NULL,
&passage_S,
&passage_T,
NULL,
NULL,
&passage_W
};

