# Project 5A - Concurrent Store

<!-- TODO: Fill this out. -->

## Design Overview:

N/A

## Collaborators:

N/A

## Extra Credit Attempted:

N/A

## How long did it take to complete the Concurrent Store portion of KVStore?

12 hours

<!-- Enter an approximate number of hours that you spent actively working on the project. -->

# Project 5B - Distributed Store

<!-- TODO: Fill this out. -->

## Design Overview:

N/A

## Collaborators:

N/A

## Extra Credit Attempted:

N/A

## How long did it take to complete the Distributed Store portion of KVStore?

7 hours

<!-- Enter an approximate number of hours that you spent actively working on the project. -->

## Who was your stakeholder pair? (<1 sentence)

Congressperson Kirby and the Freedom House Advocacy Group

## What kind of delete did you implement and why? Explain your decisions as if you were reporting to an ethical auditor who will determine whether your design is justified. Highlight and explain what you think is the most compelling reason that supports the specific kind of deletion you’ve implemented (1-2 short paragraphs)

My implementation of GDPRDelete removes all posts that a user has made, but maintains the user's account and replies to posts by the user. I choose this implementation because it gives Congressperson Kirby the CCPA Right to Delete all of their personal data while still upholding the freedom of speech rights of other consumers. While the Freedom House Advocacy Group may oppose this under the pretense that it removes evidence that affect the transparency and accountability of government officials, I believe that Congressperson's CCPA Right to Delete takes precedent. However, in an attempt to maintain the ideals of transparency, accountability, and freedom of speech, all replies to Congressperson Kirby's posts will remain on the platform. Lastly, we have choosen to keep Congressperson Kirby's account on the platform, denying their GDPR Right to be Forgotten in the interest of public health. It's important that users can still have the abstraction of Congressperson Kirby's account in order to organize discourse, and also so that scientific and historic data can be collected around public oppinion.

## What are the shortcomings of your implementation? Who are some short term and/or long term stakeholders (beyond the ones we’ve asked you to consider) who could be adversely affected by your decision? (1-2 short paragraphs)

The main shortcomming of this implementation is a lack of accountability and transparency around government officials. This implementation of GDPRDelete sets a precedent that officials are allowed to make comments that are impulsive, controversial, and even dangerous, with few long-term reprocusions. We replace a standard of foresight with the safety guards of GDPRDelete, and the result is reckless behavior, rude comments, and a complete disregard for the person you are talking to or about. This can create a toxic platform that endagers democracy through devisiveness, hate, and apathy for one another.

## How might your approach to this assignment change if you were asked to consider the interests of other stakeholders not mentioned in the scenario? (1-2 short paragraphs)

If I had to consider Sarsra Breisand, who is an American singer, actress and director, as a stakeholder, then I would be a lot more concerned with deleting posts with leaked information about her because stalking is extremely problematic. If I had to consider Angel Yoline as a stakeholder, I would think that she should take responsibility and issue an apology instead of trying to censor the situation. If I had to consider Frank and Marge Blimp as stakeholders, I would think that they should settle their dispute like adults and not play silly games of shame and censorship. If I had to consider Matt Bleat as a stakeholder, I would think that false allegations are a particularly danderous form of misinformation with very real consequences, and that the situation should be dealt with by deleting any posts promoting these allegations as truth, but allow comments broadly talking about the situation in the context of them being allegations because we also want to consider that there may be hints of truth and useful insights into the situation.
