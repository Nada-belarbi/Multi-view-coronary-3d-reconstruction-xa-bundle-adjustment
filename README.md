# Multi-view-coronary-3d-reconstruction-xa-bundle-adjustment

## Objective

Study how coronary arteries can be reconstructed in 3D from multiple X-ray angiography (XA) views and understand the geometric assumptions required for multi-view reconstruction.

## Research questions

- How is a 3D coronary artery reconstructed from two or more XA views?
- What geometric information is required from each acquisition?
- What are intrinsic and extrinsic projection parameters in an angiographic system?
- How are projection matrices constructed?
- How does triangulation work in coronary angiography?
- Why are non-coplanar and preferably near-orthogonal views useful?
- What sources of error affect the 3D reconstruction?
- How accurate are the geometric parameters provided in DICOM metadata?
- What methods are commonly used to evaluate reconstruction quality?

## Literature search keywords

- multi-view coronary angiography reconstruction
- biplane coronary artery reconstruction
- 3D coronary reconstruction from angiography
- X-ray angiography projection geometry
- coronary angiography calibration
- angiographic system geometry
- DICOM angiography geometry
- triangulation coronary angiography
- reprojection error coronary reconstruction

## Expected output

Produce a short literature review containing:

- 4–8 relevant scientific papers
- explanation of the angiographic acquisition geometry
- explanation of multi-view reconstruction
- projection and triangulation principles
- parameters required from the imaging system
- typical reconstruction errors and evaluation metrics
- a comparison table of the selected papers

## Paper comparison table

| Paper | Number of views | Dataset | Geometry model | Reconstruction method | Evaluation metric | Main result | Limitations |
|---|---|---|---|---|---|---|---|

## Deliverable

Create a Markdown document:

`docs/literature_review/multiview_reconstruction.md`

Include references and links/DOIs for all selected papers.

## Acceptance criteria

- At least 4 relevant peer-reviewed papers reviewed
- Projection geometry clearly explained
- Triangulation principle understood
- Required parameters for 3D reconstruction identified
- Main sources of reconstruction error identified
- Comparison table completed
